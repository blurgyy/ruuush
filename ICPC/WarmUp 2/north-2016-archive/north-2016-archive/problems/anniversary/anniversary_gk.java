/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem A. Anniversary Cake                                    */
/*                                                                */
/* Original idea         Niyaz Nigmatullin                        */
/* Problem statement     Dmitry Shtukenberg                       */
/* Test set              Niyaz Nigmatullin                        */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

public class anniversary_gk {
    private static Scanner in;
    private static PrintWriter out;

    private static class Solution {
        void run() {
            int w = in.nextInt();
            int h = in.nextInt();
            int ax = in.nextInt();
            int ay = in.nextInt();
            int bx = in.nextInt();
            int by = in.nextInt();
            if (ax == bx) {
                out.format("%d %d %d %d\n", 0, ay, w, by);
            } else {
                out.format("%d %d %d %d\n", ax, 0, bx, h);
            }
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("anniversary.in"));
        out = new PrintWriter("anniversary.out");

        new Solution().run();

        in.close();
        out.close();
    }
}

