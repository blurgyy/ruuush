/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem G. Gangsters in Central City                           */
/*                                                                */
/* Original idea         Vitaly Aksenov                           */
/* Problem statement     Vitaly Aksenov                           */
/* Test set              Vitaly Aksenov                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringTokenizer;
import java.util.function.IntBinaryOperator;

public class gangsters_gk {
    private static Scanner in;
    private static PrintWriter out;

    private static final int BASE = (1 << 18) - 1;

    private static class SegmentTree {
        final int base;
        final int empty;
        final IntBinaryOperator append;
        final int[] values;

        SegmentTree(final int base, final int empty, final IntBinaryOperator append) {
            this.base = base;
            this.empty = empty;
            this.append = append;
            values = new int[base * 2];
            Arrays.fill(values, empty);
        }

        void set(int i, int v) {
            i += base;
            values[i] = v;
            while (i != 0) {
                i = (i - 1) / 2;
                final int l = i * 2 + 1;
                final int r = l + 1;
                values[i] = append.applyAsInt(values[l], values[r]);
            }
        }

        int get(int l, int r) {
            l += BASE;
            r += BASE;
            int result = empty;
            while (l < r) {
                if (l % 2 == 0) {
                    result = append.applyAsInt(result, values[l]);
                }
                if (r % 2 == 1) {
                    result = append.applyAsInt(result, values[r]);
                }
                l /= 2;
                r = (r - 2) / 2;
            }
            if (l == r) {
                result = append.applyAsInt(result, values[l]);
            }
            return result;
        }
    }

    private static class Solution {
        int[] enter;
        int[] leave;
        int[] leafs;
        int[] invLeafs;
        int[] cLeafs;
        int[] grands;

        List<Integer> visits = new ArrayList<>();
        final List<List<Integer>> children = new ArrayList<>();
        final SegmentTree mins = new SegmentTree(BASE, Integer.MAX_VALUE, Math::min);
        final SegmentTree maxs = new SegmentTree(BASE, Integer.MIN_VALUE, Math::max);
        final SegmentTree lca = new SegmentTree(BASE, Integer.MAX_VALUE, Math::min);
        final SegmentTree used = new SegmentTree(BASE, 0, Integer::sum);
        int leaf;

        void run() {
            int n = in.nextInt();
            int q = in.nextInt();
            children.add(new ArrayList<>());
            for (int i = 1; i < n; i++) {
                int p = in.nextInt() - 1;
                children.get(p).add(i);
                children.add(new ArrayList<>());
            }
            enter = new int[n];
            leave = new int[n];
            leafs = new int[n];
            cLeafs = new int[n];
            invLeafs = new int[n];
            grands = new int[n];
            dfs(0, -1);
            for (int i = 0; i < visits.size(); i++) {
                lca.set(i, visits.get(i));
            }

            int[] clogged = new int[children.get(0).size()];
            int[] fails = new int[children.get(0).size()];
            int totalClogged = 0;
            int totalFails = 0;
            for (int i = 0; i < q; i++) {
                final int dv = in.next().equals("+") ? 1 : -1;
                final int v = in.nextInt() - 1;
                assert children.get(v).isEmpty();
                used.set(enter[v], dv == 1 ? 0 : 1);
                mins.set(enter[v], dv == 1 ? leafs[v] : Integer.MAX_VALUE);
                maxs.set(enter[v], dv == 1 ? leafs[v] : Integer.MIN_VALUE);
                int child = grands[v];
                final int ch = children.get(0).get(child);
                final int min = mins.get(enter[ch], leave[ch]);
                final int max = maxs.get(enter[ch], leave[ch]);
                totalClogged -= clogged[child];
                totalFails -= fails[child];
                if (min != mins.empty) {
                    final int top = lca.get(enter[invLeafs[min]], enter[invLeafs[max]]);
                    clogged[child] = 1;
                    fails[child] = used.get(enter[top], leave[top]);
                } else {
                    clogged[child] = 0;
                    fails[child] = 0;
                }
                totalClogged += clogged[child];
                totalFails += fails[child];
                out.println(totalClogged + " " + totalFails);
            }
        }

        private int dfs(final int i, final int gp) {
            visits.add(i);
            enter[i] = visits.size() - 1;
            int gdp = 0;
            for (int child : children.get(i)) {
                cLeafs[i] += dfs(child, gp == -1 ? gdp : gp);
                visits.add(i);
                gdp++;
            }
            grands[i] = gp;
            leave[i] = visits.size() - 1;
            if (enter[i] == leave[i]) {
                leafs[i] = ++leaf;
                invLeafs[leafs[i]] = i;
                cLeafs[i] = 1;
                used.set(enter[i], 1);
            }
            return cLeafs[i];
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("gangsters.in"));
        out = new PrintWriter("gangsters.out");

        new Solution().run();

        in.close();
        out.close();
    }

    static class Scanner {
        final BufferedReader reader;
        StringTokenizer tokenizer = new StringTokenizer("");

        Scanner(File file) throws FileNotFoundException {
            reader = new BufferedReader(new FileReader(file));
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        String next() {
            while (!tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new AssertionError();
                }
            }
            return tokenizer.nextToken();
        }

        void close() {
        }
    }
}

