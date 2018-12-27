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
/* Tests                                                          */
/*                                                                */
/* Author                Pavel Mavrin                             */
/******************************************************************/

import java.io.*;
import java.util.*;

/*
 * Created by pashka
 */

public class Tests {
    Random rnd = new Random(123);
    final static int MAXN = 100000;

    public static void main(String[] args) {
        new Tests().gen();
    }

    int tests = 1;

    public void writeTest(int n, int x, int y) {
        try (PrintWriter out = new PrintWriter(String.format("tests/%03d", tests++))) {

            System.err.println("Writing test " + (tests - 1));

            out.println(n + " " + x + " " + y);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void genSamples() {
        writeTest(10, 5, 7);
        writeTest(10, 3, 8);
    }

    public void gen() {
        genSamples();
        for (int i = 0; i < 5; i++) {
            int n = rnd.nextInt(10) + 3;
            int x, y;
            do {
                x = rnd.nextInt(n + 1);
                y = rnd.nextInt(n + 1);
            } while ((x + y < n) || ((x + y + n) % 2 == 1));
            writeTest(n, x, y);
        }
        writeTest(8, 5, 5);
        writeTest(8, 8, 6);
        writeTest(8, 6, 8);
        writeTest(20, 18, 20);
        writeTest(20, 20, 18);
        for (int x = 0; x <= 2; x++) {
            for (int y = 0; y <= 2; y++) {
                writeTest(2, x, y);
            }
        }
        writeTest(MAXN - 1, 0, 0);
        writeTest(MAXN - 1, 0, MAXN - 1);
        writeTest(MAXN - 1, MAXN - 1, 0);
        writeTest(MAXN - 1, MAXN / 2, MAXN / 2);
        writeTest(MAXN - 1, MAXN - 1, MAXN - 1);
        writeTest(MAXN, 0, 0);
        writeTest(MAXN, 0, MAXN);
        writeTest(MAXN, MAXN, 0);
        writeTest(MAXN, MAXN - 2, 0);
        writeTest(MAXN, 0, MAXN - 2);
        writeTest(MAXN, MAXN / 2, MAXN / 2);
        writeTest(MAXN, MAXN / 2 - 1, MAXN / 2 + 1);
        writeTest(MAXN, MAXN / 2 - 2, MAXN / 2 + 2);
        writeTest(MAXN, MAXN, MAXN);
        for (int i = 0; i < 10; i++) {
            int n;
            do {
                n = rnd.nextInt(MAXN - 2) + 3;
            } while (n % 2 == 0);
            writeTest(n, n, 0);
            writeTest(n, 0, n);
            writeTest(n, n, n);
            int x, y;
            do {
                x = rnd.nextInt(n + 1);
                y = rnd.nextInt(n + 1);
            } while (x + y < n);
            writeTest(n, x, y);
        }
        for (int i = 0; i < 10; i++) {
            int n;
            do {
                n = rnd.nextInt(MAXN - 2) + 3;
            } while (n % 2 == 1);
            writeTest(n, n, 0);
            writeTest(n, 0, n);
            writeTest(n, n, n);
            writeTest(n, n, n - 2);
            writeTest(n, n - 2, n);
            int x, y, z;
            do {
                x = 1 + rnd.nextInt(3);
                y = 1 + rnd.nextInt(3);
                z = n - x - y;
            } while (z % 2 != 0);
            writeTest(n, x + z, y + z);
            do {
                x = rnd.nextInt(n + 1);
                y = rnd.nextInt(n + 1);
            } while (x + y < n);
            writeTest(n, x, y);
            do {
                x = rnd.nextInt(n + 1);
                y = n - x + 2;
            } while (y < 0 || n < y);
            writeTest(n, x, y);
        }
    }
}

