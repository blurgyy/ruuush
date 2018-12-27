/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem K. King's Heir                                         */
/*                                                                */
/* Original idea         Andrew Stankevich                        */
/* Problem statement     Andrew Stankevich                        */
/* Test set              Pavel Kunyavskiy                         */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import javafx.util.Pair;

import java.io.File;
import java.io.PrintWriter;
import java.util.Comparator;
import java.util.Scanner;
import java.util.stream.IntStream;

public class king_gk {
    private static Scanner in;
    private static PrintWriter out;

    private static class Solution {
        int nextDate() {
            return in.nextInt() + 100 * (in.nextInt() + 100 * in.nextInt());
        }

        void run() {
            int king = nextDate();
            out.println(IntStream.range(0, in.nextInt())
                    .mapToObj(i -> new Pair<>(i + 1, nextDate()))
                    .filter(son -> son.getValue() <= king - 180000)
                    .max(Comparator.comparingInt(Pair::getValue))
                    .map(Pair::getKey).orElse(-1));
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("king.in"));
        out = new PrintWriter("king.out");

        new Solution().run();

        in.close();
        out.close();
    }
}

