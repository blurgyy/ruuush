// Solution to BribingEve, problem proposal to SWERC 2016:
//  - Radial sweep in Q2 quadrant in nlogn.
//  - Sorts events using cross product to avoid dealing with
//    numeric problems.
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

struct Point {
  Point(int x = 0, int y = 0) : x(x), y(y) {}

  bool operator<(const Point& o) const {
    // Order points in a quadrant by angle with origin:
    // Uses anti-clockwise order by returning true when the
    // cross product between the points is positive.
    return (x*o.y - y*o.x) > 0;
  }

/*
  bool operator<=(const Point& o) const {
    return (x*o.y - y*o.x) >= 0;
  }
*/
  int x, y;
};

pair<int, int> solve(const vector<Point>& points) {
  map<Point, pair<int,int> > events;

  Point begin(0, 1);
  Point end(-1, 0);

  // Add events on the borders to guarantee that we consider them.
  events[begin];
  events[end];

  int superior = 0;  // Number of points in Q1 quadrant.
  int same = 0;      // Number of points in origin.
  int active = 0;    // Number of current points in Q2 and Q4 quadrant better
                     // than origin.

  int best_pos = points.size();
  int worst_pos = 0;

  for (const auto& p : points) {
    if (p.x < 0 && p.y < 0) {}
    else if (p.x > 0 && p.y > 0) superior++;
    else if (p.x == 0 && p.y == 0) same++;
    else if (p.x <= 0 && p.y >= 0) {
      // assert(begin <= Point(p.x, p.y));
      //assert(Point(p.x, p.y) <= end);
      events[Point(p.x, p.y)].first++;
    }
    else if (p.x >= 0 && p.y <= 0) {
      //assert(begin <= Point(-p.x, -p.y));
      //assert(Point(-p.x, -p.y) <= end);
      active++;
      events[Point(-p.x, -p.y)].second++;
    }
    else assert(false);
  }

  for (const auto& e : events) {
    int tie_best_pos = superior + active - e.second.second;
    int tie_worst_pos = superior + active + e.second.first + same;
    active += e.second.first - e.second.second;

    best_pos = min(best_pos, tie_best_pos);
    worst_pos = max(worst_pos, tie_worst_pos);
  }

  return make_pair(best_pos + 1, worst_pos + 1);
}

// Reads the set of points and centers them around Maria's product.
vector<Point> read() {
  int n, cx, cy;
  cin >> n >> cx >> cy;
  vector<Point> points(n-1);
  for (Point& p : points) {
    cin >> p.x >> p.y;
    p.x -= cx;
    p.y -= cy;
  }
  return points;
}

int main() {
  auto input = read();
  auto solution = solve(input);

  for (auto& i : input)
    swap(i.x, i.y);

  assert(solution == solve(input));

  cout << solution.first << " " << solution.second << endl;
  return 0;
}
