// SWERC 2016 - Pascal's Hyper-Pyramids
// Author: Miguel Oliveira
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int N, H;

vector<int> Factor(int s) {
  vector<int> exponents(s+1, 0);
  for (int j = 2; j <= s; ++j) {
    int x = j;
    for (int i = 2; i <= x; i++) 
      while (x % i == 0) {
        ++exponents[i];
        x /= i;
      }
  }
  return exponents;
}
long long Calculate(const vector<int>& v) {
  vector<int> exponents = Factor(H-1);
  for (int x : v) {
    vector<int> d = Factor(x);
    for (size_t i = 2; i < d.size(); ++i)
      exponents[i] -= d[i];
  }
  long long res = 1;
  for (size_t i = 2; i < exponents.size(); ++i)
    for (int e = 1; e <= exponents[i]; ++e)
      res *= i;
  return res;
}

void Gen(vector<int>& v, int i, int last, int total, set<long long>& ans) {
  if (i == N) {
    ans.insert(Calculate(v));
  } else {
    for (v[i] = i+1 == N ? total : last; v[i] <= total; ++v[i]) {
      Gen(v, i+1, v[i], total - v[i], ans);
    }
  }
}

int main() {
  scanf("%d %d", &N, &H);
  set<long long> ans;
  vector<int> v(N, 0);
  Gen(v, 0, 0, H-1, ans);
  for (auto x : ans)
    printf("%lld\n", x);
  return 0;
}
