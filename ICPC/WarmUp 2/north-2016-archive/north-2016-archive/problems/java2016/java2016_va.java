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
public class java2016_va {
    public static void main(String[] args) {
        new java2016_va().run();
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
        int c = nextInt();
        if (c == 0) {
            out.println("?/?/?");
            return;
        }
        char[] vars = new char[27];
        vars[0] = '?';
        for (int i = 1; i < vars.length; i++) {
            vars[i] = (char)(i + 'a' - 1);
        }
        int tr = 13;
        for (int i = 1; i < tr; i++){
            String res = vars[i] + "=" + vars[i - 1] + " max " + vars[i - 1];
            out.println(res);
        }
        out.println(vars[tr] + "=" + vars[tr - 1] + "/" + vars[tr - 1]);
        out.println(vars[tr + 1] + "=" + vars[tr] + "+" + vars[tr]);
        for (int i = 2; i < 8; i++) {
            out.println(vars[tr + i] + "=" + vars[tr + 1] + "*" + vars[tr + i - 1]);
        }
        String ans = "";
        for (int i = 7; i >= 0; i--) {
            if ((c >> i) % 2 == 1) {
                ans += "+" + vars[tr + i];
            }
        }
        out.println(ans.substring(1));
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("java2016.in"));
            out = new PrintWriter("java2016.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

