// @EXPECTED_RESULTS@: WRONG-ANSWER

/**********************************************************************
**  This code implements a greedy solution to the microwave problem  ** 
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
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
using std::max;
using std::min;

int difference(int a, int b) { return max(a-b, b-a); }

void solve()
{
  int nrButtons, cookingTime; cin >> nrButtons >> cookingTime;
  vector<int> buttons[2]; // 0: plus buttons; 1: minus buttons
  for (int i = 0; i < nrButtons; ++i) 
  {
    int t; cin >> t;
    buttons[t < 0].push_back(t);
  }
  int nrPresses = 0;
  int currentTime = 0;
  int bestTime = 3601;
  int nrPressesToBestTime;
  while (currentTime != cookingTime)
  {
    // greedily press buttons that most reduce difference to cooking time
    int buttonset = (currentTime > cookingTime);
    if (buttons[buttonset].empty()) break; // happens when one overshoots and there are no minus buttons
    int newTime = 10000;
    for (int i = 0; i < buttons[buttonset].size(); ++i)
    {
      int candidateTime = max(min(currentTime+buttons[buttonset][i],3600),0);
      if (difference(cookingTime, candidateTime) < difference(cookingTime, newTime))
        newTime = candidateTime;        
    }
    ++nrPresses;
    currentTime = newTime;
    if (currentTime >= bestTime) break;
    if (currentTime < cookingTime) continue;
    bestTime = currentTime;
    nrPressesToBestTime = nrPresses;
  }
  cout << nrPressesToBestTime << ' ' << (bestTime - cookingTime) << endl;  
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

