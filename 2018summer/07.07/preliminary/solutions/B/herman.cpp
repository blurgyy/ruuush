// @EXPECTED_RESULTS@: CORRECT

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
using std::sort;
using std::min;
#include <queue>
using std::priority_queue;

const int MAXCOMPONENTS = 10000;
const int MAXDEPENDENCIES = 100000;
const int NEVER = (1 << 30);

struct Dependency
{
  int resource;
  int user;
  int delay;
  bool operator<(const Dependency& b) const
  {
    return (resource < b.resource);
  }
};

typedef pair<int,int> KeyId;

void solve()
{
  // read header
  int nrComponents, nrDependencies, initialFailure; 
  cin >> nrComponents >> nrDependencies >> initialFailure;
  --initialFailure;
  
  // read dependencies
  Dependency dependency[MAXDEPENDENCIES+1];
  for (int i = 0; i < nrDependencies; ++i) 
  {
    cin >> dependency[i].user >> dependency[i].resource >> dependency[i].delay;
    --dependency[i].user; --dependency[i].resource;
  }
  // sort by resource
  sort(dependency, dependency + nrDependencies);
  // add sentinel
  dependency[nrDependencies].resource = nrComponents;
  
  // construct adjacency lists
  int firstDependency[MAXCOMPONENTS];
  for (int c = 0, d = 0; c < nrComponents; ++c)
  {
    firstDependency[c] = d;
    while(dependency[d].resource == c) ++d;
  }  
  
  // initialize failure time estimates
  int earliestKnownFailure[MAXCOMPONENTS];
  bool final[MAXCOMPONENTS];
  for (int i = 0; i < nrComponents; ++i) 
  {
    earliestKnownFailure[i] = NEVER; final[i] = false;
  }
  earliestKnownFailure[initialFailure] = 0; 
  
  // initialize priority queue
  priority_queue<KeyId> Q;
  Q.push(KeyId(0, initialFailure));
  
  // run Dijkstra's
  int resourceFailure;
  int nrFailed = 0;
  while (!Q.empty())
  {
    int resource = Q.top().second;
    Q.pop();
    if (final[resource]) continue;
    final[resource] = true;
    resourceFailure = earliestKnownFailure[resource];
    ++nrFailed;
    for (int d = firstDependency[resource]; dependency[d].resource == resource; ++d)
    {
      int& userFailure = earliestKnownFailure[dependency[d].user];
      userFailure = min(userFailure, resourceFailure + dependency[d].delay);
      Q.push(KeyId(-userFailure, dependency[d].user));
    }    
  }
  
  cout << nrFailed << ' ' << resourceFailure << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

