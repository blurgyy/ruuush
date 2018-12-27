// @EXPECTED_RESULTS@: TIMELIMIT
// running time: O(n log n + k^3), where k is complexity of convex hull 

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
    
  int maxDoubleEnclosedArea = 0;
  for (vector<Point>::iterator A = convexHull.begin()+1; A->second != farAway; ++A)
    for (vector<Point>::iterator C = A+1; C->second != farAway; ++C)
    {
      int maxLeft = 0;
      int maxRight = 0;
      for (vector<Point>::iterator B = A+1; B->second != farAway; ++B)
      {
        int area = doubleClockwiseEnclosedArea(*A, *B, *C);
        maxLeft = max(maxLeft, area);
        maxRight = max(maxRight, -area);
      }
      maxDoubleEnclosedArea = max(maxDoubleEnclosedArea, maxLeft + maxRight);
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
