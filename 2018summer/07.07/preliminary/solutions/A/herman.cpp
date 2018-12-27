// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
#include <algorithm>
using std::min;
using std::max;
using std::swap;

// goal: find i s.t. k^i is divisible by n
const unsigned int MAXROOT = (1 << 16);

void solve()
{
  unsigned int n;
  unsigned int k;
  cin >> n >> k;
  int i = 0;
  for (unsigned int f = 2; n >= f && k >= f && f <= MAXROOT; ++f)
  {
    int nf = 0; while ((n % f) == 0) { n /= f; ++nf; }
    int kf = 0; while ((k % f) == 0) { k /= f; ++kf; }
    if (nf == 0) continue;
    if (kf == 0) 
    { 
      cout << "unbounded" << endl;
      return;
    }
    i = max(i, (nf-1)/kf + 1);
  }
  if (n > 1)
  {
    // k == 1 || f > MAXROOT
    if (k != n) 
    {
      cout << "unbounded" << endl;
      return;
    }
    i = max(i, 1);
  }
  cout << i << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

