// @EXPECTED_RESULTS@: WRONG-ANSWER
// running time: O(n log n) 
// idea: w.much.l.o.g., consider an optimal army base ABCD with four towers
// (army bases with three towers can be considered degenerate cases with coinciding towers)
// A and C must be the points furthest left and right of the supporting line of BD,
// B and D must be the points furthest left and right of the supporting line of AC.
// Hence all towers lie on the convex hull of the input. Moreover, as we rotate the direction
// of AC from 0 to pi, B and D together make one complete tour of the convex hull, so there can
// only be O(n) eligible diagonals BD and they can be found in O(n) time from the convex hull.
// Symmetrically, there are only O(n) eligible diagonals AC and they can be found in O(n) time.
// Now how do we find the best combination of diagonals?
// The implementation below assumes that there is an optimal solution in which A and C lie 
// furthest from one "axis" while B and D lie furthest from a second axis orthogonal to the 
// first. This allows us to find the optimal solution by simultaneously rotating four calipers 
// by 90 degrees. But the assumption does not hold, as demonstrated by the set
// (0,0) (0,4) (2,4) (2,0) (1,5), with optimal solution 8; algorithm finds 7.

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
using std::pair;
#include <algorithm>
using std::max;

const int farAway = 100000;

typedef pair<int,int> Point;

struct PositiveSlope
{
  int numerator, denominator;
  PositiveSlope(const int n, const int d): numerator(n), denominator(d) {};
  bool operator<(const PositiveSlope& s) const
  {
    return (numerator * s.denominator < s.numerator * denominator);
  }
};

int doubleClockwiseEnclosedArea(const Point& a, const Point& b, const Point& c)
{
  return
    (b.first - a.first) * (b.second + a.second) +
    (c.first - b.first) * (c.second + b.second) +
    (a.first - c.first) * (a.second + c.second);
}

void solve()
{
  // read input
  int nrLocations = 0; cin >> nrLocations;
  vector<Point> locations(nrLocations);
  for (int i = 0; i < nrLocations; ++i) 
    cin >> locations[i].first >> locations[i].second;

  // sort and check for degenerate case that all locations are on one vertical line
  sort(locations.begin(), locations.end());
  if (locations.size() == 0 || locations.back().first == locations.front().first)
  {
    cout << 0 << endl;
    return;
  }

  // build convex hull
  vector<Point> convexHull; convexHull.push_back(Point(locations[0].first-1, -farAway));
  convexHull.push_back(locations[0]);
  vector<Point> lowerHull; lowerHull.push_back(Point(locations[0].first-1,  farAway));
  lowerHull.push_back(locations[0]);
  for (vector<Point>::iterator i = ++locations.begin(); i != locations.end(); ++i)
  {
    while(convexHull.size() > 1 && 
      doubleClockwiseEnclosedArea(*(convexHull.rbegin()+1), *i, *(convexHull.rbegin())) >= 0)
      convexHull.pop_back();
    convexHull.push_back(*i);
    while(lowerHull.size() > 1 && 
      doubleClockwiseEnclosedArea(*(lowerHull.rbegin()+1), *i, *(lowerHull.rbegin())) <= 0)
      lowerHull.pop_back();
    lowerHull.push_back(*i);
  }
  for (vector<Point>::reverse_iterator i = lowerHull.rbegin(); i != lowerHull.rend(); ++i)
    convexHull.push_back(*i);
  // note: a double point or a vertical zigzag may appear where lower hull is glued 
  // to upper hull, but this does not harm the algorithm;
  // sentinels appear at both ends
    
/*
  // for debugging only
  for (vector<Point>::iterator i = convexHull.begin(); i != convexHull.end(); ++i)
    cout << i->first << ' ' << i->second << ' ';
  cout << endl;
  return;
*/
     
  // find starting points of upper left, upper right, lower right, and lower left chain
  // compute slopes (numerator/denominator pairs) for edges on each segment
  vector<Point>::iterator corner[4];
  vector<PositiveSlope> slopes[4];
  {
    vector<Point>::iterator here = convexHull.begin(); ++here; // skip sentinel
    vector<Point>::iterator next = here+1;
    corner[0] = here;
    while (next->second > here->second) 
    {
      slopes[0].push_back(PositiveSlope(next->second - here->second, next->first - here->first));
      ++here; ++next;
    }
    while (next->second == here->second) { ++here; ++next; } // skip any horizontal edge
    corner[1] = here;
    while (next->first > here->first) 
    {
      slopes[1].push_back(PositiveSlope(next->first - here->first, here->second - next->second));
      ++here; ++next;
    }
    while (next->first == here->first) { ++here; ++next; } // skip any vertical edge(s)
    corner[2] = here;
    while (next->second < here->second) 
    {
      slopes[2].push_back(PositiveSlope(here->second - next->second, here->first - next->first));
      ++here; ++next;
    }
    while (next->second == here->second) { ++here; ++next; } // skip any horizontal edge
    corner[3] = here;
    while (next->second != farAway) 
    {
      slopes[3].push_back(PositiveSlope(here->first - next->first, next->second - here->second));
      ++here; ++next;
    }
  }
  // end with sentinel zeros
  for (int i = 0; i < 4; ++i) slopes[i].push_back(PositiveSlope(0, 1));  

/*
  // for debugging only
  for (int i = 0; i < 4; ++i) 
  {
    cout << corner[i]->first << ',' << corner[i]->second << "   ";
    for (vector<PositiveSlope>::iterator j = slopes[i].begin(); j != slopes[i].end(); ++j)
      cout << j->numerator << '/' << j->denominator << ' ';
    cout << endl;
  }
  cout << endl;
  return;
*/
  
  // rotating calipers
  vector<PositiveSlope>::iterator slope[4];
  for (int i = 0; i < 4; ++i) slope[i] = slopes[i].begin();
  int maxDoubleEnclosedArea = 0;
  while (true)
  {
    maxDoubleEnclosedArea = max(maxDoubleEnclosedArea,
      (corner[1]->first - corner[0]->first) * (corner[1]->second + corner[0]->second) +
      (corner[2]->first - corner[1]->first) * (corner[2]->second + corner[1]->second) +
      (corner[3]->first - corner[2]->first) * (corner[3]->second + corner[2]->second) +
      (corner[0]->first - corner[3]->first) * (corner[0]->second + corner[3]->second)
    );
    int advance = 0;
    for (int i = 1; i < 4; ++i)
      if (*slope[advance] < *slope[i]) advance = i;
    if (slope[advance]->numerator == 0) break;
    ++corner[advance];
    ++slope[advance];
  }
  
  cout << maxDoubleEnclosedArea/2;
  if (maxDoubleEnclosedArea & 1) cout << ".5";
  cout << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}
