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
/* Author                Vitaly Aksenov                           */
/******************************************************************/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/**
 * Created by Aksenov239 on 02.10.2016.
 */
public class folding_va {
    public static void main(String[] args) {
        new folding_va().run();
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

    public int INF = 1_000_000_000;

    public int res(int W, int H, int w, int h) {
        if (w > W || h > H) {
            return INF;
        }
        int ans = 0;
        while (W > w) {
            ans++;
            W = (W + 1) / 2;
        }
        while (H > h) {
            ans++;
            H = (H + 1) / 2;
        }
        return ans;
    }

    public void solve() throws IOException {
        int W = nextInt();
        int H = nextInt();
        int w = nextInt();
        int h = nextInt();

        int ans = Math.min(res(W, H, w, h), res(W, H, h, w));
        out.println(ans >= INF ? -1 : ans);
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("folding.in"));
            out = new PrintWriter("folding.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

