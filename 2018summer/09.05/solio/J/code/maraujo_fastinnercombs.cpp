#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#define MAX 16
#define EPS 1e-5
#define DELTA 1e-4

using namespace std;

int n, m;

double comb[MAX][MAX];

double strategy[MAX];

void makeComb() {
  comb[0][0] = comb[1][1] = comb[1][0] = 1.0;
  for (int i = 2; i < MAX; ++i) {
    comb[i][0] = comb[i][i] = 1.0;
    for (int j = 1; j < i; ++j)
      comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
  }
}

double pWin(int winner, int missing, int choiceStart) {
  if (missing == 0) {
    return 1.0;
  }
  if (choiceStart > m)
    return 0.0;
  
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
  return pWin(winner, n-1, 1);
}

void normalize() {
  double sum = 0;
  for (double a: strategy) sum += a;
  for (int i = 0; i < m; i++) strategy[i] /= sum;
}

int main() {
  scanf("%d %d", &n, &m);

  makeComb();
  for (int i = 0; i < m; i++)
    strategy[i] = pow(0.5, i+1);
  normalize();

  double last[MAX];
  double pwin[m];
  double dist = 0;

  do {
    memcpy(last, strategy, sizeof(strategy));
    
    for (int i = 0; i < m; i++)
      pwin[i] = pWin(i+1);
        
    double avg = 0;
    for (double a: pwin) 
      avg += a;
    avg /= m;
      
    for (int i = 0; i < m; i++)
      if (pwin[i] > avg)
	strategy[i] = min(1.0, strategy[i] + EPS);
      else
	strategy[i] = max(1e-20, strategy[i] - EPS);
    normalize();
    
    double maior = 0, menor = 1.0;
    for (double a: pwin) {
      maior = max(maior, a);
      menor = min(menor, a);
    }

    dist = maior - menor;
  } while (dist > DELTA);
  
  for (int i = 0; i < m; i++)
    printf("%.5lf\n", strategy[i]);

  return 0;
}

