// @EXPECTED_RESULTS@: WRONG-ANSWER
// running time: ?
// idea: take the first three points as watchtowers, and then consider for 
// each subsequent input point whether the solution can be improved by
// making another selection from the current watchtowers and the new 
// candidate. If an improvement is found, consider all points again, and
// keep doing this until the solution stabilizes.
// There is no reason why this should be expected to be correct, but it 
// passes the tests so far.
// In case it does not: here is a version which keeps trying, starting
// from random permutations of the input, as long as their must be time;
// with given input parameters, 1000 passes over the input should 
// easily be feasible.

// #define DEBUGGING
#ifdef DEBUGGING
#define SHOWBASE \
for (int z = 0; z < nrTowers; ++z) \
  cout << '(' << base[z].first << ',' << base[z].second << ')'; \
cout << endl;
#else
#define SHOWBASE
#endif

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

typedef pair<int,int> Point;

int doubleClockwiseEnclosedArea(const Point& a, const Point& b, const Point& c)
{
  return
    (b.first - a.first) * (b.second + a.second) +
    (c.first - b.first) * (c.second + b.second) +
    (a.first - c.first) * (a.second + c.second);
}

int doubleArea(const Point base[4])
{
  int firstTriangle = doubleClockwiseEnclosedArea(base[0], base[1], base[2]);
  int secondTriangle = doubleClockwiseEnclosedArea(base[2], base[3], base[0]);
  if (firstTriangle < 0) return (secondTriangle <= 0 ? -(firstTriangle + secondTriangle) : 0);
  return (secondTriangle >= 0 ? (firstTriangle + secondTriangle) : 0);
}

void solve()
{
  // read input
  int nrLocations = 0; cin >> nrLocations;
  vector<Point> locations(nrLocations);
  for (int i = 0; i < nrLocations; ++i) 
    cin >> locations[i].first >> locations[i].second;
  
  Point* base = new Point[6];
  
  int bestDoubleArea = 0;
  int nrPasses = 1000;
  while (nrPasses > 0)
  {
    for (int i = 0; i < nrLocations; ++i)
      swap(locations[i], locations[i + (rand() % (nrLocations - i))]);
    base[0] = locations[0];
    base[1] = locations[1];
    int nrTowers = 2;
    int doubleArea = 0;
    for (bool improved = true; improved && nrPasses > 0; --nrPasses)
    {  
      improved = false;
      for (int i = 0; i < nrLocations; ++i) // point to include
      {
        #ifdef DEBUGGING
        cout << "Inserting (" << locations[i].first << ',' << locations[i].second << ')' << endl;
        #endif
        
        // insert in radial order around base[0]:
        int insertAfter;
        for (
          insertAfter = nrTowers-1; 
          doubleClockwiseEnclosedArea(base[0], base[insertAfter], locations[i]) < 0; 
          --insertAfter
        )
        {
          base[insertAfter+1] = base[insertAfter];
        }
        base[insertAfter+1] = locations[i];
        ++nrTowers;
        
        SHOWBASE
        
        // remove points not on convex hull
        for (bool stable = false; !stable; )
        {
          stable = true;
          for (int j = 0; j < nrTowers; ++j)
            if (doubleClockwiseEnclosedArea(base[j], base[(j+1)%nrTowers], base[(j+2)%nrTowers]) < 0)
            {
              for (int k = (j+1)%nrTowers; k < nrTowers-1; ++k)
                base[k] = base[k+1];
              --nrTowers;
              stable = false;
            }
        }
        
        SHOWBASE
        
        // choose point to remove if necessary
        if (nrTowers == 5)
        {
          base[5] = base[0];
          int bestRemoved = 0;
          int doubleAreaRemoved = doubleClockwiseEnclosedArea(base[nrTowers-1],base[0],base[1]);
          for (int k = 1; k < nrTowers; ++k)
          {
            int candidateDoubleAreaRemoved = doubleClockwiseEnclosedArea(base[k-1],base[k],base[k+1]);
            if (candidateDoubleAreaRemoved < doubleAreaRemoved)
            {
              doubleAreaRemoved = candidateDoubleAreaRemoved;
              bestRemoved = k;
            }
          }
          --nrTowers;
          for (int k = bestRemoved; k < nrTowers; ++k)
            base[k] = base[k+1];
        }
        
        SHOWBASE
        
        int newDoubleArea = 0;
        for (int k = 2; k < nrTowers; ++k)
          newDoubleArea += doubleClockwiseEnclosedArea(base[0], base[k-1], base[k]);
        if (newDoubleArea > doubleArea)
        {
          doubleArea = newDoubleArea;
          improved = true;
        }
      }
    }
    bestDoubleArea = max(bestDoubleArea, doubleArea);
  }
  
  cout << bestDoubleArea/2;
  if (bestDoubleArea & 1) cout << ".5";
  cout << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}
