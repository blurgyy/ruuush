// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setfill;

void solve()
{
  int heading;
  cin >> heading;
  int runway = ((heading % 180) + 5) / 10;
  if (runway == 0) runway = 18;
  cout << setw(2) << setfill('0') << runway << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

