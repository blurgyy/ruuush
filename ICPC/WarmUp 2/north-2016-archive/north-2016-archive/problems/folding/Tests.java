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
/* Tests                                                          */
/*                                                                */
/* Author                Georgiy Korneev                          */
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
    private static int MAX_C = 1_000_000_000;

    private static final Random random = new Random(5280549820592580955L);

    public static void main(String[] args) throws IOException {
        Files.createDirectories(root);
        test(2, 7, 2, 2);
        test(10, 6, 4, 8);
        test(5, 5, 1, 6);
        test(1, 1, 1, 1);
        test(5, 6, 6, 5);
        test(3 * 1024, 5 * 256, 5, 3);
        test(3 * 1024 + 1, 5 * 256, 3, 5);
        test(5 * 256 + 1, 3 * 1024 + 1, 5, 3);
        for (int i = 0; i < 10; i++) {
            test(random.nextInt(MAX_C) + 1, random.nextInt(MAX_C) + 1, random.nextInt(MAX_C) + 1, random.nextInt(MAX_C) + 1);
        }
        test(MAX_C, 3, 20, 2);
        test(10, MAX_C, 20, 2);
        test(MAX_C - 3, MAX_C - 1, 1, 1);
        test(MAX_C - 3, MAX_C - 1, 3, 1);
    }

    private static void test(final int W, final int H, final int w, final int h) throws FileNotFoundException {
        try (PrintWriter out = new PrintWriter(String.format("%s/%02d", root, ++nTests))) {
            System.out.println("Writing test " + nTests);
            out.println(W + " " + H);
            out.println(w + " " + h);
        }
    }
}

