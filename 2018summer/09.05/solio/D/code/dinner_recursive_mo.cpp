// Problem: Dinner Bet 
// Approach: Dynamic Programming + Probabilities
// Author: Miguel Oliveira
#include <cstdio>
#include <unordered_set>
using namespace std;
const int MAX_ITERATIONS = 700;
const int MAX_NUM = 50;
const int MAXN_PICKED = 10;

long double dp[MAX_ITERATIONS+1][MAXN_PICKED+1][MAXN_PICKED+1][MAXN_PICKED+1];
long double comb[MAX_NUM+1][MAX_NUM+1];

char done[MAX_ITERATIONS+1][MAXN_PICKED+1][MAXN_PICKED+1][MAXN_PICKED+1];
int N, D;

long double Go(int i, int x, int y, int common) {
  if (i == MAX_ITERATIONS)
    return 0.0;
  if ((x == 0 || y == 0) && common == 0)
    return i;
  if (done[i][x][y][common])
    return dp[i][x][y][common];

  long double& res = dp[i][x][y][common];
  done[i][x][y][common] = 1;
  res = 0.0;
  for (int a = 0; a <= x && a <= D; ++a) {
    for (int b = 0; b <= y && a+b <= D; ++b) {
      for (int c = 0; c <= common && a+b+c <= D; ++c) {
        // Player 1 has x+common numbers left. Player 2 has y+common numbers left.
        // Player 1 marks 'a' numbers, player 2 marks 'b' numbers, and both mark 'c' common numbers.
        long double prob =
            comb[common][c] * comb[x][a] * comb[y][b] * comb[N-x-y-common][D-a-b-c]
            / comb[N][D];
        res += prob * Go(i+1, x-a, y-b, common-c);
      }
    }
  }
  return res;
}

int main() {
  int x, num_common = 0, K;
  unordered_set<int> key;
  scanf("%d %d %d", &N, &D, &K);
  for (int i = 0; i < K; ++i) {
    scanf("%d", &x);
    key.insert(x);
  }
  for (int i = 0; i < K; ++i) {
    scanf("%d", &x);
    num_common += key.count(x);
  }
  for (int i = 0; i <= N; ++i) {
    comb[i][0] = comb[i][i] = 1.0;
    for (int j = 1; j < i; ++j)
      comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
  }
  printf("%.6Lf\n", Go(0, K-num_common, K-num_common, num_common));
  return 0;
}

