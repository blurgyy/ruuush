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
/* Author                Vitaly Aksenov                           */
/******************************************************************/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

/**
 * Created by Aksenov239 on 02.10.2016.
 */
public class anniversary_va {
    public static void main(String[] args) {
        new anniversary_va().run();
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public void solve() throws IOException {
        int x = nextInt();
        int y = nextInt();
        int ax = nextInt();
        int ay = nextInt();
        int bx = nextInt();
        int by = nextInt();

        if (ax == bx && (ax == 0 || ax == x) && Math.abs(ay - by) == 1) {
            out.println("Impossible");
            return;
        }
        if (ay == by && (ay == 0 || ay == y) && Math.abs(ax - bx) == 1) {
            out.println("Impossible");
            return;
        }

        if (ax == bx) {
            int sx = 0;
            int sy = Math.min(ay, by);
            int ex = x;
            int ey = sy + 1;

            if (((sx == ax && sy == ay) || (sx == bx && sy == by)) ||
                    ((ex == ax && ey == ay) || (ex == bx && ey == by))) {
                sx = x;
                ex = 0;
            }
            out.println(sx + " " + sy + " " + ex + " " + ey);
        } else {
            int sx = Math.min(ax, bx);
            int sy = 0;
            int ex = sx + 1;
            int ey = y;
            if (((sx == ax && sy == ay) || (sx == bx && sy == by)) ||
                    ((ex == ax && ey == ay) || (ex == bx && ey == by))) {
                sy = y;
                ey = 0;
            }
            out.println(sx + " " + sy + " " + ex + " " + ey);
        }
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("anniversary.in"));
            out = new PrintWriter("anniversary.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

