// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <algorithm>
using std::swap;
using std::max;
using std::min;
#include <vector>
using std::vector;

typedef unsigned long int BigNumber;
BigNumber maxN = (1 << 30);
vector<BigNumber> Fib; // Fib[i] = the i-th Fibonacci number

struct Solver
{
  Solver() 
  {
    BigNumber target, a, b; 
    cin >> target; a = 1; b = target-1;
    // use G_i = F_{i-1} G_2 + F_{i-2} G_1, solve for all i and keep best solution
    for (int i = 3; Fib[i] <= target; ++i)
    {
      // Note that the greatest common divider of F_{i-1} and F_{i-2} is one. 
      // Consider two solutions (G'1,G'2) and (G''1,G''2), with G'_1 < G''_1. We have:
      // F_{i-1} G'2 + F_{i-2} G'1 = F_{i-1} G''2 + F_{i-2} G''1, so:
      // F_{i-1} (G'2-G''2) = F_{i-2} (G''1-G'1), so:
      // G'2-G''2 = 0 (mod F_{i-2}) and G''1-G'1 = 0 (mod F_{i-1})
      // The other direction also holds: if there is a solution with G'2 = x, then
      // there is also a solution with G'2 = x mod F_{i-2}.
      // So we only need to try values of G_2 up to F_{i-2}-1, or, 
      // obviously, (G_i-F_{i-2})/F_{i-1}, which ever is smaller
      BigNumber maxbmod = min(b, min(Fib[i-2], (target-Fib[i-2])/Fib[i-1]));
      for (BigNumber newbmod = 1; newbmod <= maxbmod; ++newbmod)
      {
        BigNumber newa = (target - Fib[i-1]*newbmod) / Fib[i-2];
        if (target != Fib[i-1]*newbmod + Fib[i-2]*newa) continue;
        BigNumber newb = newbmod;
        if (newa > newb)
        {
          // now all is fine except that we may have a > b, so figure out
          // what is the smallest multiple of Fib[i-2] which we can add to b 
          // to solve that problem. So: minimize changeb s.t.
          // b + changeb <= a - changa; changeb * Fib[i-1] = changea * Fib[i-2]
          // changeb + changea <= (a-b); 
          // changeb / Fib[i-2] <= (a-b) / (Fib[i-2] + Fib[i-1])
          newb += Fib[i-2] * (1 + (newa - newb - 1) / (Fib[i-2] + Fib[i-1]));
          // now check if we are not reducing a to 0 or less as a result:
          if (Fib[i-1] * newb >= target) continue;
          newa = (target - Fib[i-1]*newb) / Fib[i-2];
        }        
        if (newb > b) continue;
        if (newb == b && newa >= a) continue;
        a = newa; b = newb;
      }
    }
    cout << a << ' ' << b << endl;
  }
};

int main()
{
  Fib.push_back(0);
  Fib.push_back(1);
  while (Fib.back() < maxN) Fib.push_back(Fib[Fib.size()-1] + Fib[Fib.size()-2]);
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) { Solver s; }
}

