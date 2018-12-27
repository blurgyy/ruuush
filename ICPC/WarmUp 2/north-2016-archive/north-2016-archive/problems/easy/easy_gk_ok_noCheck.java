/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem E. Easy Reading                                        */
/*                                                                */
/* Original idea         Dmitry Shtukenberg                       */
/* Problem statement     Boris Minaev                             */
/* Test set              Boris Minaev                             */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.*;
import java.util.function.BiFunction;
import java.util.stream.LongStream;

public class easy_gk_ok_noCheck {
    private static final int MAX_L = 100_000;
    private static final long MODULO = 123456791;
    private static final long[] X_POWERS = LongStream.iterate(1, r -> (r * 254857209) % MODULO).limit(MAX_L * 4).toArray();
    private static final long[] Y_POWERS = LongStream.iterate(1, r -> (r * 580734587) % MODULO).limit(MAX_L * 4).toArray();
    private static final BiFunction<Object, Integer, Integer> REMOVE = (k, c) -> c == 1 ? null : c - 1;

    private static Scanner in;
    private static PrintWriter out;

    private static class Cell {
        final int x;
        final int y;
        final long hash;

        Cell(final int x, final int y) {
            this.x = x;
            this.y = y;
            hash = (X_POWERS[x] * Y_POWERS[y]) % MODULO;
        }
    }

    private static class Image {
        final NavigableMap<Cell, Integer> rows = new TreeMap<>(Comparator.<Cell>comparingInt(c -> c.y).thenComparingInt(c -> c.x));
        final NavigableMap<Integer, Integer> cols = new TreeMap<>();
        long hash = 0;

        boolean add(final Cell cell) {
            final boolean added = rows.merge(cell, 1, Integer::sum) == 1;
            if (added) {
                hash = (hash + cell.hash) % MODULO;
                cols.merge(cell.x, 1, Integer::sum);
            }
            return added;
        }

        void remove(final Cell cell) {
            final boolean removed = rows.compute(cell, REMOVE) == null;
            if (removed) {
                hash = (hash - cell.hash + MODULO) % MODULO;
                cols.compute(cell.x, REMOVE);
            }
        }

        int getFilled() {
            return rows.size();
        }
    }

    private static class Solution {
        void run() {
            in.nextInt();
            in.nextLine();
            final String s = in.nextLine();
            final List<Cell> cells = new ArrayList<>();
            Cell current = new Cell(MAX_L * 2, MAX_L * 2);
            for (char ch : ("#" + s).toCharArray()) {
                current = new Cell(
                        current.x + (ch == 'l' ? -1 : ch == 'r' ? 1 : 0),
                        current.y + (ch == 'u' ? -1 : ch == 'd' ? 1 : 0)
                );
                cells.add(current);
            }
            int rows = in.nextInt();
            in.nextInt();

            final Image image = new Image();
            for (int r = 0; r < rows; r++) {
                int c = 0;
                for (char cell : in.next().toCharArray()) {
                    if (cell == 'X') {
                        image.add(new Cell(c, r));
                    }
                    c++;
                }
            }

            final Image paper = new Image();
            final int imageX = image.cols.firstKey();
            final int imageY = image.rows.firstKey().y;
            final Iterator<Cell> tail = cells.iterator();
            for (Cell cell : cells) {
                if (paper.add(cell)) {
                    while (paper.getFilled() > image.getFilled()) {
                        paper.remove(tail.next());
                    }
                    final int dx = paper.cols.firstKey() - imageX;
                    final int dy = paper.rows.firstKey().y - imageY;
                    if (image.rows.size() == paper.rows.size() && ((image.hash * X_POWERS[dx] % MODULO) * Y_POWERS[dy]) % MODULO == paper.hash) {
                        out.println("YES");
                        out.println((cells.indexOf(tail.next()) + 1) + " " + cells.indexOf(cell));
                        return;
                    }
                }
            }
            out.println("NO");
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("easy.in"));
        out = new PrintWriter("easy.out");

        new Solution().run();

        in.close();
        out.close();
    }
}

