/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem I. Integral Polygons                                   */
/*                                                                */
/* Original idea         Niyaz Nigmatullin                        */
/* Problem statement     Dmitry Shtukenberg                       */
/* Test set              Niyaz Nigmatullin                        */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.*;
import java.util.StringTokenizer;

public class integral_gk {
    private static Scanner in;
    private static PrintWriter out;

    private static class Solution {
        void run() {
            int n = in.nextInt();
            int[] xs = new int[n];
            int[] ys = new int[n];
            for (int i = 0; i < n; i++) {
                xs[i] = in.nextInt();
                ys[i] = in.nextInt();
            }
            long sum = -1;
            boolean[] odd = new boolean[n + 1];
            for (int k = 1; k <= n; k++) {
                odd[k] = odd[k - 1] ^ ((xs[k % n] - xs[(k - 1) % n] & 1) != 0 & (ys[k % n] - ys[(k - 1) % n] & 1) != 0);
            }
            int[][][] c = new int[2][2][2];
            for (int k = 0; k < n; k++) {
                final int v = odd[k] ? 1 : 0;
                final int x = xs[k] & 1;
                final int y = ys[k] & 1;
                sum += c[v][x][y] + c[v][x ^ 1][y] + c[v][x][y ^ 1] + c[v ^ 1][x ^ 1][y ^ 1];
                if (k > 0) {
                    c[odd[k - 1] ? 1 : 0][xs[k - 1] & 1][ys[k - 1] & 1]++;
                }
            }
            out.println(odd[n] ? 0 : sum);
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("integral.in"));
        out = new PrintWriter("integral.out");

        new Solution().run();

        in.close();
        out.close();
    }


    static class Scanner {
        final BufferedReader reader;
        StringTokenizer tokenizer = new StringTokenizer("");

        Scanner(File file) throws FileNotFoundException {
            reader = new BufferedReader(new FileReader(file));
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        String next() {
            while (!tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new AssertionError();
                }
            }
            return tokenizer.nextToken();
        }

        void close() {
        }
    }
}

