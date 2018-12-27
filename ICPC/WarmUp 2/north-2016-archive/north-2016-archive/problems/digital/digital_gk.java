/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem D. Digital Addition                                    */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Mikhail Dvorkin                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class digital_gk {
    private static Scanner in;
    private static PrintWriter out;

    private static class Answer {
        final int[] values;
        final Answer prev;

        Answer(final int[] values, final Answer prev) {
            this.values = values;
            this.prev = prev;
        }
    }

    private static class Solution {
        static final int[][] DIGITS = {
                {1, 1, 1, 0, 1, 1, 1},
                {0, 0, 1, 0, 0, 1, 0},
                {1, 0, 1, 1, 1, 0, 1},
                {1, 0, 1, 1, 0, 1, 1},
                {0, 1, 1, 1, 0, 1, 0},
                {1, 1, 0, 1, 0, 1, 1},
                {1, 1, 0, 1, 1, 1, 1},
                {1, 0, 1, 0, 0, 1, 0},
                {1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 0, 1, 1}
        };
        void run() {
            int[][][][][] transitions = new int[1 << 4][1 << 5][1 << 4][1 << 2][];
            for (int i = 0; i <= 9; i++) {
                final int[] I = DIGITS[i];
                for (int j = 0; j <= 9; j++) {
                    final int[] J = DIGITS[j];
                    for (int c = 0; c <= 1; c++) {
                        int k = i + j + c;
                        final int[] K = DIGITS[k % 10];
                        transitions
                                [pack(I[1], I[4] | J[1], J[4] | K[1], K[4])]
                                [pack(I[0], I[3] | J[0], I[6] | J[3] | K[0], J[6] | K[3], K[6])]
                                [pack(I[2], I[5] | J[2], J[5] | K[2], K[5])]
                                [pack(k / 10, c)] = new int[]{i, j, k % 10};
                    }
                }
            }

            int n = in.nextInt();
            final int[][] segments = new int[][] {
                    readInts(n),
                    readInts(n + 1),
                    readInts(n),
                    readInts(n + 1),
                    readInts(n),
                    readInts(n + 1),
                    readInts(n),
                    readInts(n + 1),
                    readInts(n),
            };

            final Answer[][][] answers = new Answer[n + 1][1 << 4][1 << 1];
            answers[0][0][0] = new Answer(null, null);
            for (int p = 0; p < n; p++) {
                int lv = pack(segments[1][p], segments[3][p], segments[5][p], segments[7][p]);
                int m = pack(segments[0][p], segments[2][p], segments[4][p], segments[6][p], segments[8][p]);
                for (int lc = 0; lc < 2; lc++) {
                    for (int lb = 0; lb < 1 << 4; lb++) {
                        for (int rc = 0; rc < 2; rc++) {
                            for (int rlb = 0; rlb < 1 << 4; rlb++) {
                                for (int rrb = 0; rrb < 1 << 4; rrb++) {
                                    if ((lb | rlb) == lv && answers[p][lb][lc] != null && transitions[rlb][m][rrb][pack(lc, rc)] != null) {
                                        answers[p + 1][rrb][rc] = new Answer(transitions[rlb][m][rrb][pack(lc, rc)], answers[p][lb][lc]);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Answer answer = answers[n][pack(segments[1][n], segments[3][n], segments[5][n], segments[7][n])][0];
            if (answer == null) {
                out.println("NO");
            } else {
                final int[][] result = new int[3][n];
                for (int i = n - 1; i >= 0; i--) {
                    for (int j = 0; j < 3; j++) {
                        result[j][i] = answer.values[j];
                    }
                    answer = answer.prev;
                }
                out.println(Arrays.stream(result)
                        .map(row -> Arrays.stream(row).mapToObj(Integer::toString).collect(Collectors.joining()))
                        .collect(Collectors.joining("\n")));
            }
        }

        private int[] readInts(final int n) {
            return IntStream.generate(() -> in.nextInt()).limit(n).toArray();
        }

        private int pack(int... ints) {
            return Arrays.stream(ints).reduce(0, (r, i) -> r * 2 + i);
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("digital.in"));
        out = new PrintWriter("digital.out");

        new Solution().run();

        in.close();
        out.close();
    }
}

