// @EXPECTED_RESULTS@: WRONG-ANSWER
// solution method: sample all rpm from 10000 to 0
// should not work IMHO, but passes all tests so far

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

typedef long long int bigInt;
const int maxGears = 10;

void solve()
{
  int nrGears; cin >> nrGears;
  bigInt a[1+maxGears], b[1+maxGears], c[1+maxGears];
  for (int i = 1; i <= nrGears; ++i)
    cin >> a[i] >> b[i] >> c[i];
  int bestGear = 1;
  bigInt bestMax = 0;
  bigInt bestrpm = 0;
  for (int gear = 1; gear <= nrGears; ++gear)
    for (bigInt rpm = 5000; rpm >= 0; --rpm)
      if (-a[gear]*rpm*rpm + b[gear]*rpm + c[gear] > bestMax)
      {
        bestMax = -a[gear]*rpm*rpm + b[gear]*rpm + c[gear];
        bestGear = gear;
        bestrpm = rpm;
      }
  cout << bestGear << endl; //<< ' ' << bestrpm << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}
