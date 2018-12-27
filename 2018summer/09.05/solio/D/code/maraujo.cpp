#include <cstdio>
#include <algorithm>
#include <set>

#define MAXDAYS 1000
#define MAXN 51
#define MAXKEYSIZE 11
#define MAXDRAW 11

using namespace std;

int n, k, d;

double prob[MAXDAYS][MAXKEYSIZE][MAXKEYSIZE][MAXKEYSIZE]; // probabilidade de ao fim de D dias, um jogador precisar de I numeros, o outro de J e ainda K em comum

long double combs[MAXN][MAXN];

void buildCombs() {
  combs[0][0] = combs[1][1] = combs[1][0] = 1;
  for (int i = 2; i < MAXN; i++) {
    combs[i][0] = combs[i][i] = 1;
    for (int j = 1; j < i; j++)
      combs[i][j] = combs[i-1][j] + combs[i-1][j-1];
  }
}

int main() {
  scanf("%d %d %d", &n, &d, &k);
  set<int> numbers;
  for (int i = 0; i < k; i++) {
    int temp;
    scanf("%d", &temp);
    numbers.insert(temp);
  }
  int overlap = 0;
  for (int i = 0; i < k; i++) {
    int temp;
    scanf("%d", &temp);
    if (numbers.find(temp) != numbers.end())
      overlap++;
  }
  buildCombs();

  int single = k-overlap;
  //printf("%d %d\n", single, overlap);
  
  prob[0][single][single][overlap] = 1;
    
  for (int day = 1; day < MAXDAYS; day++) 
    for (int i = 0; i <= single; i++)
      for (int j = 0; j <= single; j++)
	for (int c = 0; c <= overlap; c++) {
	  if (c == 0 && (i == 0 || j == 0)) continue;
	  for (int ii = 0; ii <= min(i,d); ii++)
	    for (int jj = 0; jj <= min(d-ii, j); jj++)
	      for (int cc = 0; cc <= min(d-ii-jj,c); cc++) {
		if (n - (i-ii) - (j-jj) - (c-cc) < d-ii-jj-cc) continue;
		//printf("%d %d %d %d %d %d %d %lf %Lf %Lf %Lf\n", day, i, j, c, ii, jj, cc, prob[day-1][i][j][c], combs[i][ii], combs[j][jj], combs[c][cc]);
		prob[day][i-ii][j-jj][c-cc] += prob[day-1][i][j][c]*combs[i][ii]*combs[j][jj]*combs[c][cc]*combs[n-i-j-c][d-ii-jj-cc]/combs[n][d];
	      }
	}

  
  /*
  for (int day = 0; day < MAXDAYS; day++)
    for (int i = 0; i <= k; i++)
      for (int j = 0; j <= k; j++)
	for (int c = 0; c <= k; c++)
	  printf("%d %d %d %d %lf\n", day, i, j, c, prob[day][i][j][c]);
  */	  

  double expected = 0;
  for (int day = 1; day < MAXDAYS; day++) {
    expected += day*prob[day][0][0][0];
    for (int i = 1; i <= k; i++)
      expected += day*(prob[day][i][0][0] + prob[day][0][i][0]);
  }
  printf("%lf\n", expected);

  return 0;
}
