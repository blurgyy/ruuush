// Problem: Dinner Bet
// Approach: Dynamic Programming + Probabilities
// Author: Miguel Oliveira
import java.util.Scanner;
import java.util.HashSet;

public class DinnerBet {
  private static final int MAX_ITERATIONS = 2000;

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    int d = in.nextInt();
    int k = in.nextInt();
    HashSet<Integer> key = new HashSet<Integer>();
    for (int i = 0; i < k; i++) {
      key.add(in.nextInt());
    }
    int num_common = 0;
    for (int i = 0; i < k; i++) {
      num_common += key.contains(in.nextInt()) ? 1 : 0;
    }
    System.out.printf("%.6f\n", Solve(n, k, d, num_common));
  }

  private static double Solve(int n, int k, int d, int num_common) {
    double[][] comb = new double[n+1][n+1];
    comb[0][0] = comb[1][1] = comb[1][0] = 1.0;
    for (int i = 2; i <= n; ++i) {
      comb[i][0] = comb[i][i] = 1.0;
      for (int j = 1; j < i; ++j)
        comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    }
    double[][][][] dp = new double[2][k+1][k+1][k+1];
    int resi = 1;
    for (int i = MAX_ITERATIONS-1; i >= 0; --i, resi ^= 1) 
      for (int common = 0; common <= k; ++common) {
        for (int x = 0; x <= Math.min(k-common, n-common); ++x) {
          for (int y = 0; y <= Math.min(k-common, n-x-common); ++y) {
            if ((x == 0 || y == 0) && common == 0) {
              dp[resi][common][x][y] = i;
              continue;
            }
            dp[resi][common][x][y] = 0;
            for (int a = 0; a <= x && a <= d; ++a) {
              for (int b = 0; b <= y && a+b <= d; ++b) {
                int c_upto = Math.min(common, d-a-b);
                for (int c = Math.max(0, (d-a-b)-(n-x-y-common)); c <= c_upto; ++c) {
                  // Player 1 has x+common numbers left. Player 2 has y+common numbers left.
                  // Player 1 marks 'a' numbers, player 2 marks 'b' numbers, and both mark 'c' common numbers.
                  double p = comb[common][c] * comb[x][a] * comb[y][b] * comb[n-x-y-common][d-a-b-c] / comb[n][d];
                  dp[resi][common][x][y] += p * dp[resi^1][common-c][x-a][y-b];
                }
              }
            }
          }
        }
      }
    return dp[resi^1][num_common][k-num_common][k-num_common];
  }
}
