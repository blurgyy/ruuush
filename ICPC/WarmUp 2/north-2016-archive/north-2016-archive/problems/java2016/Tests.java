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
/* Tests                                                          */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class Tests {
    static int nTests = 0;
    static final File root = new File("tests");

    static final Random random = new Random(5712632832434238417L);

    static final int MODULO = 256;
    static final List<Integer> tests = new ArrayList<Integer>();

    public static void main(String[] args) throws IOException {
        powers(2);
        powers(3);
        powers(10);
        for (int i = 0; i < 10; i++) {
            tests.add(random.nextInt(MODULO));
        }
        final List<Integer> tests = Tests.tests.stream()
                .sorted().distinct()
                .filter(a -> 0 <= a && a < MODULO)
                .collect(Collectors.toList());

        new File("tests").mkdirs();
        for (final int test : tests) {
            try (PrintWriter out = new PrintWriter(String.format("%s/%02d", root.getName(), ++nTests))) {
                System.out.println("Writing test " + nTests);
                out.println(test);
            }
        }
    }

    private static void powers(final int n) {
        int sum1 = 0;
        int sum2 = 0;
        int p = 1;
        for (int i = 1; i <= MODULO; i *= n, p *= -1) {
            addPM(i);
            addPM(sum1 += i);
            addPM(sum2 += i * p);
        }
    }

    private static void addPM(final int i) {
        tests.add(i - 1);
        tests.add(i);
        tests.add(i + 1);
    }
}

