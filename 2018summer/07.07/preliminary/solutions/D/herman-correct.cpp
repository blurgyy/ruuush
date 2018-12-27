// Implements quadratic-time, linear-space, dynamic-programming solution
// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
#include <algorithm>
using std::min;

const unsigned int MAXFLOORS = 1500;
const unsigned int MAXPERFLOOR = 1500;
const unsigned int MAXANGER = (1 << 31);

int main()
{
  int nrTestCases; cin >> nrTestCases;
  while (--nrTestCases >= 0)
  {
    int nrFloors; cin >> nrFloors;
    // table to maintain number of students for given and lower floors:
    unsigned int students[MAXFLOORS+1];
    students[0] = 0;
    for (int i = 1; i <= nrFloors; ++i)
    {
      cin >> students[i];
      students[i] += students[i-1];
    }
    // table to maintain anger up to and including current floor if last stop is on given floor
    // note: annoyance for skipping is counted starting with the floor of destination, and not for the floor where students get out
    unsigned int anger[MAXFLOORS+1];
    anger[0] = 0;
    for (int currentFloor = 1; currentFloor <= nrFloors; ++currentFloor)
    {
      anger[currentFloor] = MAXANGER;
      for (int lastStop = 0; lastStop < currentFloor; ++lastStop)
      {
        anger[currentFloor] = min(anger[currentFloor], anger[lastStop] + students[nrFloors] - students[currentFloor]);
        anger[lastStop] += students[currentFloor] - students[lastStop];      
      }
    }
    cout << anger[nrFloors] << endl;
  }
}
