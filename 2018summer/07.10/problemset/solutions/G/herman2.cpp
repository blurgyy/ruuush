// @EXPECTED_RESULTS@: CORRECT
// (possible wrong answer due to floating point errors, but no longer an issue with new problem description)
// running time: O(n) 

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

typedef long double myNumber;
const int maxGears = 10;

void solve()
{
  int nrGears; cin >> nrGears;
  int optGear = 0;
  myNumber optRPM;
  myNumber optTorque;
  for (int i = 1; i <= nrGears; ++i)
  {
    myNumber a, b, c, RPM, torque;
    cin >> a >> b >> c;
    RPM = b / (a*2.0);
    torque = -a*RPM*RPM + b*RPM + c;
    if (optGear == 0 || torque > optTorque)
    {
      optGear = i;
      optTorque = torque;
      optRPM = RPM;
    }
  }    
  cout << optGear << endl; //' ' << (int) (optRPM + 0.5) << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}
