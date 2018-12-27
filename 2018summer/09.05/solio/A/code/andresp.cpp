#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <cstdio>
using namespace std;

constexpr double EPSILON = 1e-10;

struct Point {
  double x;
  double y;
};

ostream& operator<<(ostream& lhs, const Point& rhs) {
  return lhs << "{" << rhs.x << ", " << rhs.y << "}";
}

double dist(Point a) {
  return sqrt(a.x*a.x + a.y*a.y);
}

double dist(Point a, Point b) {
  return dist(Point{a.x - b.x, a.y - b.y});
}

Point closestInRange(Point target, double la, double lb) {
  double d = dist(target);
  // Avoid divisions by "zero".
  if (d < EPSILON) {
    return Point{la, 0};
  }
  if (la <= d && d <= lb)
    return target;
  if (d < la) {
    return Point{target.x * la / d, target.y * la / d };
  }
  return Point{target.x * lb / d, target.y * lb / d };
}

// A triangle with lengths {a, b, c} always satisfy: a < b + c, b < a + c, c < a + b.
// This methods picks a valid 'c' within [min_c, max_c]
double findC(double a, double b, double min_c, double max_c) {
  min_c = max(min_c, abs(a-b));
  max_c = min(max_c, a + b);

  // We can return any 'c' between [min_c, max_c]
  // assert(max_c - min_c > -EPSILON);
  return (min_c + max_c) / 2;
}

double contactAngle(double target_dist, double last_segment, double la, double lb) {
  double a = target_dist;
  double b = last_segment;
  double c = findC(a, b, la, lb);

  // Avoid div by zero.
  if (abs(2 * a * b) < EPSILON) return 0;

  // Avoid numeric errors before acos.
  double x = (a*a + b*b - c*c) / (2 * a * b);
  double caped_x = max(min(x, 1.0), -1.0);
  assert(abs(caped_x - x) < EPSILON);
  return acos(caped_x);
}

// Returns the point where a joint needs to be.
Point findPoint(Point target, double segment_size, double la, double lb) {
  double target_dist = dist(target);
  double angle = contactAngle(target_dist, segment_size, la, lb);
  double l1 = segment_size;

  Point target_vec;
  if (target_dist < EPSILON) target_vec = Point{1.0, 0.0};
  else target_vec = Point{ -target.x / target_dist, -target.y / target_dist };

  Point contact_vec = {
    target_vec.x * cos(angle) - target_vec.y * sin(angle),
    target_vec.x * sin(angle) + target_vec.y * cos(angle)
  };

  Point joint = {target.x + contact_vec.x * l1, target.y + contact_vec.y * l1 };
  return joint;
}

struct Problem {
  vector<double> segments;
  Point target;

  vector<double> angles;
  vector<Point> coordinates;

  Point run(size_t n, double la, double lb) {
    angles.resize(segments.size());
    coordinates.resize(segments.size());
    if (n == segments.size()) {
      Point closest = closestInRange(target, la, lb);
      // cerr << "Closest reachable point is: " << closest << " with distance: " << dist(target, closest) << endl;
      return closest;
    }

    double length = segments[n];

    double mla = length > lb ? length - lb :
                 length > la ? 0 : la - length;

    double mlb = lb + length;

    Point next_joint = run(n + 1, mla, mlb);
    Point this_joint = findPoint(next_joint, length, la, lb);

    angles[n] = atan2(next_joint.y - this_joint.y, next_joint.x - this_joint.x);
    coordinates[n] = next_joint;

    // cerr << next_joint << endl;
    assert(abs(dist(this_joint, next_joint) - length) < EPSILON);
    return this_joint;
  }

  void printAngles() {
    for (const auto& a : angles) {
      printf("%0.9lf\n", a);
    }
  }

  void printCoordinates() {
    for (const auto& c : coordinates) {
      printf("%0.3lf %0.3lf\n", c.x, c.y);
    }
  }
};

Problem readInput() {
  int N;
  cin >> N;
  vector<double> segments(N);
  for (auto& s : segments) cin >> s;
  Point target;
  cin >> target.x >> target.y;
  return Problem{segments, target};
}

int main() {
  auto p = readInput();
  p.run(0, 0, 0);
  p.printCoordinates();
  return 0;
}
