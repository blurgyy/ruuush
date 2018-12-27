// SWERC 2016: White Rabbit 
// Author: Miguel Oliveira
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
const int MAXT = 1000;
const int MAXE = 200;
const int MOD = 13;

struct Trip {
  vector<int> locations;
  int duration, am;
} trips[MAXT];

struct Equation {
  vector<int> coef;
  int res;
} eq[MAXT];

int N, A, R, T, ea[MAXT], eb[MAXT], dist[MAXE+1][MAXE+1];
map<pair<int,int>, int> ind;

void BuildEquations() {
  for (int i = 0; i < T; ++i) {
    eq[i].coef.assign(MAXE, 0);
    eq[i].res = trips[i].duration;
    for (int j = 1; j < trips[i].am; ++j) {
      int a = trips[i].locations[j-1], b = trips[i].locations[j];
      pair<int,int> p{min(a, b), max(a, b)};
      if (!ind.count(p)) {
        ea[ind.size()] = p.first;
        eb[ind.size()] = p.second;
        int pos = ind.size(); // careful with undefined behavior
        ind[p] = pos;
      }
      if (++eq[i].coef[ind[p]] == 13)
        eq[i].coef[ind[p]] = 0;
    }
  }
}
void Gauss() {
  int nvar = ind.size();
  vector<int> invMod(MOD, 0);
  for (int i = 1; i < MOD; ++i)
    for (int j = 1; j < MOD; ++j)
      if (i * j % MOD == 1)
        invMod[i] = j;
  for (int row = 0; row < T && row < nvar; ++row) {
    int pos = row;
    while (eq[pos].coef[row] == 0)  // in this problem, we're guaranteed to find > 0.
      ++pos;
    swap(eq[row], eq[pos]);
    int d = invMod[eq[row].coef[row]];
    for (int j = row; j < nvar; ++j)
      eq[row].coef[j] = eq[row].coef[j] * d % MOD;
    eq[row].res = eq[row].res * d % MOD;
    for (int i = 0; i < T; ++i) 
      if (i != row) {
        int c = eq[i].coef[row];
        eq[i].res = (eq[i].res - c * eq[row].res % MOD + MOD) % MOD;
        for (int j = row; j < nvar; ++j)
          eq[i].coef[j] = (eq[i].coef[j] - c * eq[row].coef[j] % MOD + MOD) % MOD;
      }
  }
}
int Solve() {
  BuildEquations();
  Gauss();
  memset(dist, 0x3f, sizeof dist);
  for (int i = 1; i <= N; ++i)
    dist[i][i] = 0;
  for (size_t j = 0; j < ind.size(); ++j) 
    dist[ea[j]][eb[j]] = dist[eb[j]][ea[j]] = eq[j].res;
  
  for (int k = 1; k <= N; ++k)      // N is small. Floyd is good enough.
    for (int i = 1; i <= N; ++i)
      for (int j = 1; j <= N; ++j)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
  return dist[A][R];
}
int main() {
  int x;
  scanf("%d %d %d %d", &N, &A, &R, &T);
  for (int i = 0; i < T; ++i) {
    scanf("%d %d", &trips[i].duration, &trips[i].am);
    for (int j = 0; j < trips[i].am; ++j) {
      scanf("%d", &x);
      trips[i].locations.push_back(x);
    }
  }
  printf("%d\n", Solve());
  return 0;
}
