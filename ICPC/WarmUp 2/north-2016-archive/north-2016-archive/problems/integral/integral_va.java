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
/* Author                Vitaly Aksenov                           */
/******************************************************************/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * Created by Aksenov239 on 15.10.2016.
 */
public class integral_va {
    public static void main(String[] args) {
        new integral_va().run();
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
        int n = nextInt();
        int[] x = new int[n];
        int[] y = new int[n];

        for (int i = 0; i < n; i++) {
            x[i] = nextInt();
            y[i] = nextInt();
        }

        long area = 0;
        long[] prefix = new long[n + 1];
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            area += (long) x[i] * y[j] - (long) x[j] * y[i];
            prefix[i + 1] = area;
        }
        if ((area & 1) == 1) {
            out.println(0);
            return;
        }

        long ans = 0;
        int[] total = new int[8];
        // state: x - even or odd, y - even or odd, prefix sum - even or odd
        for (int i = 0; i < n; i++) {
            for (int ex = 0; ex < 2; ex++) {
                for (int ey = 0; ey < 2; ey++) {
                    for (int ep = 0; ep < 2; ep++) {
                        if ((prefix[i] + ep + ex * y[i] + ey * x[i]) % 2 == 0) {
                            ans += total[ex * 4 + ey * 2 + ep];
                        }
                    }
                }
            }
            total[(x[i] & 1) * 4 + (y[i] & 1) * 2 + (int) (prefix[i] & 1)]++;
        }
        out.println(ans - n);
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("integral.in"));
            out = new PrintWriter("integral.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

