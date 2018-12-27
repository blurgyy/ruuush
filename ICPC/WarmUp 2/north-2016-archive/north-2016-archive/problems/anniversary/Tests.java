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
/* Tests                                                          */
/*                                                                */
/* Author                Niyaz Nigmatullin                        */
/******************************************************************/

import java.io.*;
import java.util.*;

public class Tests {
    static int nTests = 0;
    static final File root = new File("tests");
    static final int MAXN = 1000000000;

    static final Random random = new Random(50216L);

    public static void main(String[] args) throws IOException {
        test(7, 3, 2, 2, 3, 2);
        randomTest(3, 1000000000);
        randomTest(MAXN, 3);
        randomTest(MAXN, MAXN);
        test(MAXN, MAXN, MAXN / 2, MAXN / 2, MAXN / 2 + 1, MAXN / 2);
        test(MAXN, MAXN, MAXN / 2, MAXN / 2, MAXN / 2, MAXN / 2 - 1);
        test(MAXN, MAXN, MAXN / 2, MAXN / 2, MAXN / 2 - 1, MAXN / 2 + 1);
        test(MAXN, MAXN / 10, MAXN - 1, MAXN / 10 - 1, MAXN - 2, MAXN / 10 - 1);
        test(MAXN, MAXN, MAXN - 1, MAXN / 2, MAXN - 1, MAXN / 2 + 1);
        for (final int N : new int[]{10, 1000, 1000000, 900000000}) {
            for (int i = 0; i < 3; i++) {
                randomTest(random.nextInt(N) + 3, random.nextInt(N) + 3);
            }
        }
        for (int i = 0; i < 15; i++) {
            randomTest(random.nextInt(10) + 3, random.nextInt(10) + 3);            
        }
    }

    public static void randomTest(int n, int m) throws FileNotFoundException {
        int x1, y1, x2, y2;
        do {
            x1 = random.nextInt(n - 1) + 1;
            y1 = random.nextInt(m - 1) + 1;
            x2 = random.nextInt(n - 1) + 1;
            y2 = random.nextInt(m - 1) + 1;
        } while (x1 == x2 && y1 == y2);
        test(n, m, x1, y1, x2, y2);
    }

    public static void test(int n, int m, int x1, int y1, int x2, int y2) throws FileNotFoundException {
        try (PrintWriter out = new PrintWriter(String.format("%s/%02d", root.getName(), ++nTests))) {
            System.out.println("Writing test " + nTests);
            out.println(n + " " + m + " " + x1 + " " + y1 + " " + x2 + " " + y2);
        }
    }
}

