/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem J. Java2016                                            */
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

public class java2016_gk_ok_max {
    private static Scanner in;
    private static PrintWriter out;

    private static class Solution {
        int var = 0;

        String macro(String def) {
            String v = "" + (char) ('a' + var++);
            out.println(v + " = " + def);
            return v;
        }

        String max(String v) {
            return macro(v + " max " + v);
        }

        String twice(String p) {
            return macro("(" + p + " + " + p + ")");
        }

        void run() {
            int n = in.nextInt();
            String[] p = new String[8];
            p[0] = max(max(max(max(max(max(max(max(max(max(max("?")))))))))));

            p[1] = twice(p[0]);
            for (int i = 2; i < p.length; i++) {
                p[i] = macro(p[i - 1] + " * " + p[1]);
            }

            out.print("?/?/?");
            for (int i = 0; i < p.length; i++) {
                if ((n & (1 << i)) != 0) {
                    out.print((i == 0 || i % 2 == 1 ? " - " : " + ") + p[i]);
                }
            }
            out.println();
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("java2016.in"));
        out = new PrintWriter("java2016.out");

        new Solution().run();

        in.close();
        out.close();
    }
}

