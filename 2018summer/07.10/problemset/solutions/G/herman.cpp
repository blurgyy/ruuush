// @EXPECTED_RESULTS@: CORRECT
// running time: O(n) 

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

typedef unsigned long long int bigInt;
const int maxGears = 10;

void solve()
{
  int nrGears; cin >> nrGears;
  bigInt a[1+maxGears], b[1+maxGears], c[1+maxGears];
  for (int i = 1; i <= nrGears; ++i)
    cin >> a[i] >> b[i] >> c[i];
  int o = 1;
  for (int i = 2; i <= nrGears; ++i)
    if (a[o]*b[i]*b[i] + 4*a[i]*a[o]*c[i] > 
        a[i]*b[o]*b[o] + 4*a[i]*a[o]*c[o])
      o = i;
  cout << o << endl; //' ' << (b[o] + a[o]) / (2*a[o]) << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}
