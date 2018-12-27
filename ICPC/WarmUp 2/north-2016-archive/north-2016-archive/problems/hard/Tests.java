/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem H. Hard Cuts                                           */
/*                                                                */
/* Original idea         Georgiy Korneev                          */
/* Problem statement     Gennady Korotkevich                      */
/* Test set              Gennady Korotkevich                      */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author                Gennady Korotkevich                      */
/******************************************************************/

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Random;

public class Tests {
    private static int nTests = 0;
    private static final Path root = Paths.get("tests");
    private static int MAX_W = 60;

    private static final Random random = new Random(5280549820592580955L);

    public static void main(String[] args) throws IOException {
        Files.createDirectories(root);
        sample();
        test(5, 5, -1);
        test(10, 10, -1);
        test(15, 15, -1);
        test(20, 20, -1);
        test(30, 30, -1);
        test(MAX_W, MAX_W, 1);
        test(MAX_W, MAX_W, 10);
        test(MAX_W, MAX_W, 100);
        test(MAX_W, MAX_W, 1000);
        test(MAX_W, MAX_W, -1);
    }

    private static void sample() throws FileNotFoundException {
        try (PrintWriter out = new PrintWriter(String.format("%s/%02d", root, ++nTests))) {
            System.out.println("Writing test " + nTests);
            out.println("3");
            out.println("5 3");
            out.println("5 6");
            out.println("4 4");
            //out.println("13 11");
        }
    }

    private static void test(final int W, final int H, int T) throws FileNotFoundException {
        try (PrintWriter out = new PrintWriter(String.format("%s/%02d", root, ++nTests))) {
            System.out.println("Writing test " + nTests);
            if (T == -1) {
                T = W * H;
            }
            T = Math.min(T, W * H);
            out.println(T);
            int[][] a = new int[W][H];
            for (int i = 0; i < T; i++) {
                int w, h;
                do {
                    w = random.nextInt(W);
                    h = random.nextInt(H);
                } while (a[w][h] > 0);
                out.println((w + 1) + " " + (h + 1));
                a[w][h]++;
            }
        }
    }
}

