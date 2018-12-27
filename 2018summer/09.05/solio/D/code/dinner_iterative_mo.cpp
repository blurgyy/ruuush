// Problem: Dinner Bet 
// Approach: Dynamic Programming + Probabilities
// Author: Miguel Oliveira
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <unordered_set>
using namespace std;
const int MAX_ITERATIONS = 1000;
const int MAXN = 50;
const int MAXK = 10;

double dp[2][MAXK+1][MAXK+1][MAXK+1], comb[MAXN+1][MAXN+1];

double Solve(int N, int K, int D, int num_common) {
  for (int i = 0; i <= N; ++i) {
    comb[i][0] = comb[i][i] = 1.0;
    for (int j = 1; j < i; ++j)
      comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
  }
  int resi = 1;
  for (int i = MAX_ITERATIONS-1; i >= 0; --i, resi ^= 1) 
    for (int common = 0; common <= K; ++common) 
      for (int x = 0; x <= min(K-common, N-common); ++x) 
        for (int y = 0; y <= min(K-common, N-x-common); ++y) {
          if ((x == 0 || y == 0) && common == 0) {
            dp[resi][common][x][y] = i;
            continue;
          }
          dp[resi][common][x][y] = 0;
          for (int a = 0; a <= x && a <= D; ++a) {
            for (int b = 0; b <= y && a+b <= D; ++b) {
              int c_upto = min(common, D-a-b);
              for (int c = max(0, (D-a-b)-(N-x-y-common)); c <= c_upto; ++c) {
                // Player 1 has x+common numbers left. Player 2 has y+common numbers left.
                // Player 1 marks 'a' numbers, player 2 marks 'b' numbers, and both mark 'c' common numbers.
                double prob = comb[common][c] * comb[x][a] * comb[y][b]
                              * comb[N-x-y-common][D-a-b-c]
                              / comb[N][D];
                dp[resi][common][x][y] += prob * dp[resi^1][common-c][x-a][y-b];
              }
            }
          }
        }
  return dp[resi^1][num_common][K-num_common][K-num_common];
}

int main() {
  int x, num_common = 0, N, K, D;
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
  printf("%.6f\n", Solve(N, K, D, num_common));
  return 0;
}

