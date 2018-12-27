// @EXPECTED_RESULTS@: CORRECT

/**********************************************************************
**  This code implements a solution to the microwave problem in      **
**  O(h n) time, where h is the number of seconds in an hour         ** 
**********************************************************************/

// #define DEBUGGING
#ifdef DEBUGGING
#define REPORT(activity) cerr << activity << endl;
#else
#define REPORT(activity)
#endif

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <stack>
using std::stack;
#include <vector>
using std::vector;

void solve()
{
  int nrButtons, cookingTime; cin >> nrButtons >> cookingTime;
  vector<int> buttons(nrButtons);
  for (int i = 0; i < nrButtons; ++i) cin >> buttons[i];
  if (cookingTime == 0) 
  {
    cout << "0 0" << endl;
    return;
  }
  stack<int>* fewerPresses = new stack<int>;
  stack<int>* morePresses  = new stack<int>;
  vector<int> minPresses(3601);
  minPresses[0] = 0; const int tooMany = 3601; 
  for (int i = 1; i <= 3600; ++i) minPresses[i] = tooMany;
  int bestTime = 3600;
  fewerPresses->push(0);
  
  for (int nrPresses = 1; minPresses[cookingTime] == tooMany && nrPresses < tooMany; ++nrPresses)
  {
    while (!fewerPresses->empty())
    {
      int currentTime = fewerPresses->top();
      fewerPresses->pop();
      for (int i = 0; i < nrButtons; ++i)
      {
        int newTime = currentTime + buttons[i];
        if (newTime <= 0) continue;
        if (newTime > 3600) newTime = 3600;
        if (minPresses[newTime] < tooMany) continue;
        if (newTime >= cookingTime && newTime < bestTime) bestTime = newTime;
        minPresses[newTime] = nrPresses;
        morePresses->push(newTime);
      }
    }
    swap(fewerPresses, morePresses);
  }  
  
  delete fewerPresses;
  delete morePresses;
  
  cout << minPresses[bestTime] << ' ' << bestTime-cookingTime << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

