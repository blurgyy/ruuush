// @EXPECTED_RESULTS@: CORRECT
// running time: O(n log n) 
/**********************************************************************
Idea: w.much.l.o.g., consider an optimal army base ABCD with four 
towers (army bases with three towers can be considered degenerate cases 
with coinciding towers, and will be handled naturally).

A and C must be the points furthest left and right of the supporting 
line of BD. Similarly, B and D must be the points furthest left and 
right of the supporting line of AC. Hence all towers lie on the convex 
hull of the input, which we construct in O(n log n) time.

We will generate a sufficient set of candidates for an optimal solution 
in order of decreasing slope of the diagonal DB. As we rotate the 
direction of BD from downward to leftward, A will move up on the upper 
left chain of the convex hull while C moves down on the lower right 
chain of the convex hull. By simulating this rotation we can therefore 
generate all eligible diagonals AC and, moreover, we generate them in 
order of decreasing slope. Hence, from going through all possible 
slopes of DB in decreasing order, we can generate the slopes (and 
precise locations) of the corresponding diagonals AC in decreasing 
order, from which we derieve the precise locations of B (moving down 
on the upper right chain of the convex hull) and D (moving up on the 
lower left chain). As A, B, C and D are each making a clockwise tour of
a quarter of the convex hull, the total number of events during the 
rotation, and hence, the total number of candidate solutions generated, 
is only O(n).
**********************************************************************/

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
  // Note: a double point or a vertical zigzag may appear where lower hull is glued 
  // to upper hull because I was too lazy to handle degeneracies with points on a common
  // vertical line, but this does not harm the algorithm. Sentinels appear at both ends.
    
/*
  // for debugging only
  for (vector<Point>::iterator i = convexHull.begin(); i != convexHull.end(); ++i)
    cout << i->first << ' ' << i->second << ' ';
  cout << endl;
  return;
*/
     
  // find starting points of upper left, upper right, lower right, and lower left chain,
  // and compute slopes (numerator/denominator pairs) for edges on each chain
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
    PositiveSlope diagonalBisectorSlope(corner[2]->first - corner[0]->first, corner[0]->second - corner[2]->second);
    int advance = 0;
    if (diagonalBisectorSlope < *slope[1] || diagonalBisectorSlope < *slope[3])
      advance = (*slope[1] < *slope[3] ? 3 : 1);
    else
      advance = (*slope[2] < *slope[0] ? 0 : 2);
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
