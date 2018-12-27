/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem B. Boys and Girls                                      */
/*                                                                */
/* Original idea         Pavel Mavrin                             */
/* Problem statement     Pavel Mavrin                             */
/* Test set              Pavel Mavrin                             */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class boysgirls_gk {
    private static Scanner in;
    private static PrintWriter out;

    private static class Solution {
        String replicate(final String s, final int n) {
            return IntStream.range(0, n).mapToObj(i -> s).collect(Collectors.joining());
        }

        String half(int n, int b, int g) {
            int bg = b + g - n;
            return replicate("BG", bg / 2) + replicate("G", n - b) + replicate("B", n - g);
        }

        void run() {
            int n = in.nextInt();
            int b = in.nextInt();
            int g = in.nextInt();
            if (n % 2 == 1) {
                int bg = b + g - n;
                if (n <= b + g && g <= n && b <= n && (b + g != n || n == g || n == b) && bg % 2 == 0) {
                    final String s = half(n, b, g);
                    out.println(mix(s, (s + s).substring(n / 2 + 1)).substring(0, n));
                    return;
                }
            } else if ((b + g) % 2 == 0) {
                final int n2 = n / 2;
                for (int b1 = Math.max(0, b - n2); b1 <= Math.min(b, n2); b1++) {
                    int start = parity(Math.max(Math.max(0, n2 - b1), g - n2), n2 - b1);
                    final int bound = Math.min(Math.min(g, n2), b + g - n2 - b1);
                    for (int g1 = start; g1 <= bound; g1 += 2) {
                        final int b2 = b - b1;
                        final int g2 = g - g1;
                        if (b1 + g1 != n2 || g1 == 0 || b1 == 0) {
                            if (b2 + g2 != n2 || g2 == 0 || b2 == 0) {
                                out.println(mix(half(n2, b1, g1), half(n2, b2, g2)));
                                return;
                            }
                        }
                    }
                }
            }
            out.println("Impossible");
        }

        private int parity(final int value, final int p) {
            return (value + p) % 2 == 0 ? value : value + 1;
        }

        private String mix(final String s1, final String s2) {
            return IntStream.range(0, s1.length())
                    .mapToObj(i -> s1.charAt(i) +  "" + s2.charAt(i))
                    .collect(Collectors.joining());
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("boysgirls.in"));
        out = new PrintWriter("boysgirls.out");

        new Solution().run();

        in.close();
        out.close();
    }
}

