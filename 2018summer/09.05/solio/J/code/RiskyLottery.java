import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class RiskyLottery {
  static final int MAX = 16;
  static final double EPS = 1e-5;
  static final double DELTA = 1e-4;

  static int n, m;

  static double[][] comb = new double[MAX][MAX];

  static double[] strategy;

  static void makeComb() {
    comb[0][0] = comb[1][1] = comb[1][0] = 1.0;
    for (int i = 2; i < MAX; ++i) {
      comb[i][0] = comb[i][i] = 1.0;
      for (int j = 1; j < i; ++j)
        comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    }
  }

  static double pWin(int winner, int missing, int choiceStart) {
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

  static double pWin(int winner) {
    return pWin(winner, n-1, 1);
  }

  static void normalize() {
    double sum = 0;
    for (double a: strategy) sum += a;
    for (int i = 0; i < m; i++) strategy[i] /= sum;
  }

  public static void main(String[] args) throws IOException {
    Scanner sc = new Scanner(System.in);
    n = sc.nextInt();
    m = sc.nextInt();

    makeComb();
    strategy = new double[m];
    for (int i = 0; i < m; i++)
      strategy[i] = Math.pow(0.5, i+1);
    normalize();

    double[] last;
    double[] pwin = new double[m];
    double dist = 0;
    do {
      last = strategy.clone();

      for (int i = 0; i < m; i++)
        pwin[i] = pWin(i+1);

      double avg = 0;
      for (double a: pwin) {
        avg += a;
      }
      avg /= m;

      for (int i = 0; i < m; i++)
        if (pwin[i] > avg)
          strategy[i] = Math.min(1.0, strategy[i] + EPS);
        else
          strategy[i] = Math.max(1e-20, strategy[i] - EPS);
      normalize();

      double maior = 0, menor = 1.0;
      for (double a: pwin) {
        maior = Math.max(maior, a);
        menor = Math.min(menor, a);
      }
      dist = maior - menor;
    } while (dist > DELTA);

    for (double v : strategy)
	System.out.printf("%.5f\n", v);
  }
}
