#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include <vector>

#define DELTA 1e-4
#define MAXN 10
#define MAXM 10

using namespace std;

int n, m;
double p[MAXM];
double probW[MAXM];

int pos[MAXM];

map<vector<int>, int> wins[MAXM];

int lowestUniqueNumber() {
  for (int i = 0; i < m; i++)
    if (pos[i]==1) return i;
  return -1;
}

void addToCombs(int winner) {
  vector<int> *v = new vector<int>(pos, pos+m);
  if (wins[winner].find(*v) != wins[winner].end())
    wins[winner][*v]++;
  else
    wins[winner][*v] = 1;
}

void placement(int k) {
  if (k == n) {
    int winner = lowestUniqueNumber();
    if (winner != -1)
      addToCombs(winner);
  }
  else 
    for (int i = 0; i < m; i++) {
      pos[i]++;
      placement(k+1);
      pos[i]--;
    }
}


void buildCombs() {
  memset(pos, 0, sizeof(pos));
  placement(0);
}

void probWinning() {
  memset(probW, 0, sizeof(probW));
  for (int i = 0; i < m; i++) {
    for (map<vector<int>, int>::iterator it = wins[i].begin(); it != wins[i].end(); it++) {
      double prod = it->second;
      for (int j = 0; j < m; j++)
	if (j != i)
	  for (int k = 0; k < it->first[j]; k++)
	    prod *= p[j];
      probW[i] += prod;
    }
    probW[i] /= m;
  }
}

void normalize() {
  double sum = 0;
  for (int i = 0; i < m; i++) sum += p[i];
  for (int i = 0; i < m; i++) p[i] /= sum;
}

int main() {
  scanf("%d %d", &n, &m);
  
  buildCombs();

  /*
  for (int i = 0; i < m; i++) {
    printf("%d: \n", i);
    for (map<vector<int>, int>::iterator it = wins[i].begin(); it != wins[i].end(); it++) {
      printf("%d = ", it->second);
      for (int j = 0; j < m; j++)
	for (int k = 0; k < it->first[j]; k++)
	  printf("%d ", j);
      putchar('\n');
    }
  }
  */

  for (int i = 0; i < m; i++) p[i] = pow(0.5, i+1);
  normalize();
 
  double maior, menor;
  int cnt = 0;
  do {
    probWinning();
    double avg = 0;
    maior = 0; menor = 1;
    for (int i = 0; i < m; i++) {
      maior = max(maior, probW[i]);
      menor = min(menor, probW[i]);
      avg += probW[i];
    }
    avg /= m;
    
    double sum = 0;
    for (int i = 0; i < m; i++) {
      //printf("%d %lf %lf\n", i, p[i], probW[i]);
      p[i] += (probW[i]-avg);
      sum += p[i];
    }

    for (int i = 0; i < m; i++) 
      p[i] /= sum;
    cnt++;
  } while (maior - menor > DELTA);

  for (int i = 0; i < m; i++)
    printf("%0.3lf\n", p[i]);

  return 0;
}
