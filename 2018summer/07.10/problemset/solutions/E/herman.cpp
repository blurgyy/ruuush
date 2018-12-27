// @EXPECTED_RESULTS@: CORRECT

/**********************************************************************
Algorithm: sort by increasing x; maintain set I of interesting 
candidates w.r.t. y and z, ordered by increasing y and decreasing z. 
Consider candidates in order of increasing x. Every candidate X is 
dominated in x by all condidates considered before, and will dominate 
all candidates yet to be considered in x. Therefore X is interesting if 
and only if it is not dominated in y and z by candidates that are in I 
already. Find the last candidate Y in I with lower y. If Y dominates X,
skip X. Otherwise remove all successors of Y that are dominated by X, 
and insert X.
**********************************************************************/

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <algorithm>
using std::sort;
#include <vector>
using std::vector;
#include <set>
using std::set;

struct Solver
{
  struct Engineer 
  { 
    int communication, programming, knowledge;
    Engineer(int c = 0, int p = 0, int k = 0): communication(c), programming(p), knowledge(k) {};
    struct OrderByCommunication
    {
      bool operator()(const Engineer& a, const Engineer& b) const { return a.communication < b.communication; }
    };
    struct OrderByProgramming
    {
      bool operator()(const Engineer& a, const Engineer& b) const { return a.programming < b.programming; }
    };
    bool dominates(const Engineer& other) const
    {
      return 
        programming < other.programming &&
        knowledge < other.knowledge;
    }
  };
  
  Solver() 
  {
    int nrOnFile; cin >> nrOnFile;
    vector<Engineer> onFile(nrOnFile);
    for (int i = 0; i < nrOnFile; ++i)
      cin >> onFile[i].communication >> onFile[i].programming >> onFile[i].knowledge;
    sort(onFile.begin(), onFile.end(), Engineer::OrderByCommunication());
    set<Engineer, Engineer::OrderByProgramming> interesting;
    interesting.insert(Engineer(0,0,onFile.size()+1));
    interesting.insert(Engineer(0,onFile.size()+1,0));
    int nrInteresting = 0;
    for (vector<Engineer>::iterator i = onFile.begin(); i != onFile.end(); ++i)
    {
      set<Engineer>::iterator firstWorseProgrammer = interesting.lower_bound(*i);
      set<Engineer>::iterator lastBetterProgrammer = firstWorseProgrammer; --lastBetterProgrammer;
      if (lastBetterProgrammer->dominates(*i)) continue;
      set<Engineer>::iterator firstNonDominatedEngineer = firstWorseProgrammer;
      while (i->dominates(*firstNonDominatedEngineer)) ++firstNonDominatedEngineer;
      interesting.erase(firstWorseProgrammer, firstNonDominatedEngineer);
      interesting.insert(*i);
      ++nrInteresting;
    }
    cout << nrInteresting << endl;
  }
};

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) { Solver s; }
}

