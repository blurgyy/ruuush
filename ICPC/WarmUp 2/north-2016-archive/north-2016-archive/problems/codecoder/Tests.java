/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem C. CodeCoder vs TopForces                              */
/*                                                                */
/* Original idea         Egor Kulikov                             */
/* Problem statement     Egor Kulikov                             */
/* Test set              Egor Kulikov                             */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author                Egor Kulikov                             */
/******************************************************************/

import java.io.*;
import java.util.*;

import static java.lang.Math.min;
import static java.util.Arrays.*;

public class Tests {
    private static final int MAX_RATING = 1_000_000;
    private static final int MAX_N = 100_000;
    static int nTests = 0;
    static final File root = new File("tests");

    static final Random random = new Random(50216L);

    public static void main(String[] args) throws IOException {
        test(new int[]{2, 3, 1, 4}, new int[]{3, 2, 1, 5});
        test(new int[]{2, 3, 1}, new int[]{2, 3, 1});
        test(new int[]{1, 2, 0});
        randomTest(MAX_N);
        test(new int[]{0});
        int[] sizes = {10, 100, 1000, 10000, 30000, 100000};
        for (int i = 0; i < sizes.length; i++) {
            for (int j = 0; j <= i; j++) {
                parts(sizes[i], sizes[j]);
                int n = random.nextInt(sizes[i]) + 1;
                int m = random.nextInt(min(sizes[j], n)) + 1;
                parts(n, m);
            }
        }
    }

    private static void parts(int n, int m) throws FileNotFoundException {
        int[] div = new int[m - 1];
        Set<Integer> was = new HashSet<>();
        for (int i = 0; i < m - 1; i++) {
            do {
                div[i] = random.nextInt(n - 1) + 1;
            } while (was.contains(div[i]));
            was.add(div[i]);
        }
        sort(div);
        div = copyOf(div, m);
        div[m - 1] = n;
        int start = 0;
        int[] p = new int[n];
        for (int limit : div) {
            for (int i = start; i < limit; i++) {
                int at = random.nextInt(i - start + 1) + start;
                p[i] = p[at];
                p[at] = i;
            }
            start = limit;
        }
        test(p);
    }

    public static void randomTest(int n) throws FileNotFoundException {
        int[] p = new int[n];
        for (int i = 0; i < n; i++) {
            int at = random.nextInt(i + 1);
            p[i] = p[at];
            p[at] = i;
        }
        test(p);
    }

    public static void test(int[] p) throws FileNotFoundException {
        int n = p.length;
        int[] cc = generateRandomRatings(n);
        int[] tfBase = generateRandomRatings(n);
        int[] tf = new int[n];
        for (int i = 0; i < n; i++) {
            tf[i] = tfBase[p[i]];
        }
        for (int i = 0; i < n; i++) {
            int at = random.nextInt(i + 1);
            int temp = cc[i];
            cc[i] = cc[at];
            cc[at] = temp;
            temp = tf[i];
            tf[i] = tf[at];
            tf[at] = temp;
        }
        test(cc, tf);
    }

    private static int[] generateRandomRatings(int n) {
        Set<Integer> was = new HashSet<>();
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            do {
                result[i] = random.nextInt(MAX_RATING) + 1;
            } while (was.contains(result[i]));
            was.add(result[i]);
        }
        sort(result);
        return result;
    }

    public static void test(int[] cc, int[] tf) throws FileNotFoundException {
        try (PrintWriter out = new PrintWriter(String.format("%s/%02d", root.getName(), ++nTests))) {
            System.out.println("Writing test " + nTests);
            out.println(cc.length);
            for (int i = 0; i < cc.length; i++) {
                out.println(cc[i] + " " + tf[i]);
            }
        }
    }
}

