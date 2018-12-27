/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem F. Folding                                             */
/*                                                                */
/* Original idea         Georgiy Korneev                          */
/* Problem statement     Georgiy Korneev                          */
/* Test set              Georgiy Korneev                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

public class folding_gk {
    private static Scanner in;
    private static PrintWriter out;

    private static class Solution {
        void run() {
            int W = in.nextInt();
            int H = in.nextInt();
            int w = in.nextInt();
            int h = in.nextInt();

            int s1 = solve(W, H, w, h);
            int s2 = solve(W, H, h, w);
            if (s1 == -1 || s2 == -1) {
                out.println(Math.max(s1, s2));
            } else {
                out.println(Math.min(s1, s2));
            }
        }

        private int solve(final int W, final int H, final int w, final int h) {
            if (W < w || H < h) {
                return -1;
            }
            return solve(W, w) + solve(H, h);
        }

        private int solve(int W, final int w) {
            int c = 0;
            while (W > w) {
                W = (W + 1) / 2;
                c++;
            }
            return c;
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("folding.in"));
        out = new PrintWriter("folding.out");

        new Solution().run();

        in.close();
        out.close();
    }
}

