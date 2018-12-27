// @EXPECTED_RESULTS@: TIMELIMIT

/**********************************************************************
Algorithm: read in candidates one by one and maintain in array. Upon 
reading a new candidate, throw out all who are dominated. Enter 
candidate if dominated itself. 
**********************************************************************/

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <vector>
using std::vector;

struct Solver
{
  struct Engineer 
  { 
    int communication, programming, knowledge;
    Engineer(std::istream& i)
    {
      i >> communication >> programming >> knowledge;
    }
    bool dominates(const Engineer& other) const
    {
      return 
        communication < other.communication &&
        programming < other.programming &&
        knowledge < other.knowledge;
    }
  };
  
  Solver() 
  {
    int nrOnFile; cin >> nrOnFile;
    vector<Engineer> candidates;
    for (int i = 0; i < nrOnFile; ++i)
    {
      Engineer e(cin);
      bool dominated = false;
      for (vector<Engineer>::iterator j = candidates.begin(); j != candidates.end(); )
      {
        dominated = j->dominates(e);
        if (dominated) break;
        if (!e.dominates(*j))
        {
          ++j;
          continue;
        }
        *j = candidates.back();
        candidates.pop_back();        
      }
      if (dominated) continue;
      candidates.push_back(e);
    } 
    cout << candidates.size() << endl;
  }
};

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) { Solver s; }
}

