import java.util.*;
import java.io.*;
import static java.lang.Math.*;

class Point {
  double x;
  double y;
  Point(double x, double y) { this.x = x; this.y = y; }
}

class ac_andresp {
/*
ostream& operator<<(ostream& lhs, const Point& rhs) {
  return lhs << "{" << rhs.x << ", " << rhs.y << "}";
}
*/
static final double EPSILON = 1e-10;

static double dist(Point a) {
  return sqrt(a.x*a.x + a.y*a.y);
}

static double dist(Point a, Point b) {
  return dist(new Point(a.x - b.x, a.y - b.y));
}

static Point closestInRange(Point target, double la, double lb) {
  double d = dist(target);
  // Avoid divisions by "zero".
  if (d < EPSILON) {
    return new Point(la, 0);
  }
  if (la <= d && d <= lb)
    return target;
  if (d < la) {
    return new Point(target.x * la / d, target.y * la / d );
  }
  return new Point(target.x * lb / d, target.y * lb / d );
}

// A triangle with lengths {a, b, c} always satisfy: a < b + c, b < a + c, c < a + b.
// This methods picks a valid 'c' within [min_c, max_c]
static double findC(double a, double b, double min_c, double max_c) {
  min_c = max(min_c, abs(a-b));
  max_c = min(max_c, a + b);

  // We can return any 'c' between [min_c, max_c]
  assert(max_c - min_c > -EPSILON);
  return (min_c + max_c) / 2;
}

static double contactAngle(double target_dist, double last_segment, double la, double lb) {
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
static Point findPoint(Point target, double segment_size, double la, double lb) {
  double target_dist = dist(target);
  double angle = contactAngle(target_dist, segment_size, la, lb);
  double l1 = segment_size;

  Point target_vec;
  if (target_dist < EPSILON) target_vec = new Point(1.0, 0.0);
  else target_vec = new Point(-target.x / target_dist, -target.y / target_dist);

  Point contact_vec = new Point(
    target_vec.x * cos(angle) - target_vec.y * sin(angle),
    target_vec.x * sin(angle) + target_vec.y * cos(angle)
  );

  Point joint = new Point(target.x + contact_vec.x * l1, target.y + contact_vec.y * l1 );
  return joint;
}

static class Problem {
  final double[] segments;
  final Point target;
  final Point[] coordinates;
  final double[] angles;
  Problem(double[] segments, Point target) {
    this.segments = segments;
    this.target = target;
    angles = new double[segments.length];
    coordinates = new Point[segments.length];
  }

  Point run(int n, double la, double lb) {
    if (n == segments.length) {
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
    for (double a : angles) {
      System.out.printf("%0.9f\n", a);
    }
  }

  void printCoordinates() {
    for (Point c : coordinates) {
      System.out.printf("%.3f %.3f\n", c.x, c.y);
      //System.out.printf("%0.3f %0.3f\n", c.x, c.y);
    }
  }
}

static Problem readInput() {
  Scanner in = new Scanner(System.in);
  int N;
  N = in.nextInt();
  double[] segments = new double[N];
  for (int i=0;i < N; i++) segments[i] = in.nextDouble();
  Point target = new Point(in.nextDouble(), in.nextDouble());
  return new Problem(segments, target);
}

public static void main(String[] args) {
  Problem p = readInput();
  p.run(0, 0, 0);
  p.printCoordinates();
}
}
