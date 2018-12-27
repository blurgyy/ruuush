#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
using namespace std;

#define MAX_COMB 16

int comb[MAX_COMB + 1][MAX_COMB + 1] = {};
int N, M;
vector<double> strategy;

double pWin(int winner, int missing, int choiceStart) {
  if (missing == 0) {
    return 1.0;
  }
  if (choiceStart > M) return 0.0;

  double sum = 0.0;
  sum += pWin(winner, missing, choiceStart + 1);

  double prob = 1.0;
  for (int i = 1; i <= missing; ++i) {
    prob *= strategy[choiceStart - 1];
    if (choiceStart == winner) continue;
    if (i == 1 && choiceStart < winner) {
      continue;
    }
    sum += comb[missing][i] * prob * pWin(winner, missing - i, choiceStart + 1);
  }
  return sum;
}

double pWin(int winner) {
  return pWin(winner, N - 1, 1);
}

void makeComb() {
  comb[0][0] = comb[1][1] = comb[1][0] = 1.0;
  for (int i = 2; i <= MAX_COMB; ++i) {
    comb[i][0] = comb[i][i] = 1.0;
    for (int j = 1; j < i; ++j)
      comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
  }
}

void normalize() {
  double sum = accumulate(strategy.begin(), strategy.end(), 0.0);
  for (auto& s : strategy) s /= sum;
}

void debugSplit() {
  cout << "split:"; for (int i = 1; i <= M; ++i) cout << " " << pWin(i); cout << endl;
}

int main() {
  makeComb();

  cin >> N >> M;
  strategy.resize(M);

  srand(time(nullptr));
  for (auto& s : strategy) s = (rand() % 1000) + 1;
  normalize();

  vector<double> pwin(M);
  vector<double> last(M);
  for (int it = 0; ; it++) {
    if (it % 100 == 0) {
      double max_diff = 0.0;
      for (int i = 0; i != M; ++i) {
        max_diff = max(max_diff, abs(last[i] - strategy[i]));
      }
      if (max_diff < 1e-8) break;
      last = strategy;
    }
    // debugSplit();

    for (int i = 0; i != M; ++i) pwin[i] = pWin(i + 1); 
    double avg = accumulate(pwin.begin(), pwin.end(), 0.0) / pwin.size();
    
    double mstep = 0.0;
    for (int i = 0; i != M; ++i) {
      double deriv = (pwin[i] - avg);
      mstep = max(mstep, abs(deriv));
      strategy[i] = max(1e-20, strategy[i] + deriv);
    }
    normalize();
  }

  if (false) {
    // debugSplit();
    double s = pWin(1);
    for (int i = 2; i <= M; ++i) {
      assert(abs(pWin(i) - s) < 1.0e-8);
    }
  }

  for (auto s : strategy) printf("%0.5lf\n", s);
  return 0;
}
