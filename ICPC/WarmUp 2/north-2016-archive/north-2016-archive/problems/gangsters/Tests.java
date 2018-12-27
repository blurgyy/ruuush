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
/* Tests                                                          */
/*                                                                */
/* Author                Vitaly Aksenov                           */
/******************************************************************/

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.TreeSet;

public class Tests {
    int MAX_N = 100000;
    int MAX_Q = 100000;

    Random rnd = new Random(239);

    public static void main(String[] args) {
        new Tests().gen();
    }

    public class Vertex implements Comparable<Vertex> {
        int v, p;
        int r;

        public Vertex(int v, int p) {
            this.v = v;
            this.p = p;
            this.r = rnd.nextInt();
        }

        public int compareTo(Vertex p) {
            return r == p.r ? v - p.v : r - p.r;
        }
    }

    public void shuffle(int[] p, int[] q) {
        ArrayList<Integer>[] e = lists(p.length + 1);
        for (int i = 0; i < e.length; i++) {
            e[i] = new ArrayList<>();
        }
        for (int i = 0; i < p.length; i++) {
            e[p[i]].add(i + 1);
        }

        int[] nv = new int[e.length];
        TreeSet<Vertex> ts = new TreeSet<>();
        for (int v : e[0]) {
            ts.add(new Vertex(v, 0));
        }
        for (int i = 1; i < e.length; i++) {
            Vertex x = ts.pollFirst();
            nv[x.v] = i + 1;
            p[i - 1] = x.p;
            for (int v : e[x.v]) {
                ts.add(new Vertex(v, i));
            }
        }
        for (int i = 0; i < q.length; i++) {
            q[i] = (int) Math.signum(q[i]) * nv[Math.abs(q[i]) - 1];
        }
    }

    int tests = 1;

    public void writeTest(int[] p, int[] qs) {
        try {
            PrintWriter out = new PrintWriter(String.format("tests/%02d", tests++));

            System.err.println("Writing test " + (tests - 1));

            out.println((p.length + 1) + " " + qs.length);
            for (int i = 0; i < p.length; i++) {
                out.print((i != 0 ? " " : "") + (p[i] + 1));
            }
            out.println();
            for (final int q : qs) {
                if (q < 0) {
                    out.println("- " + (-q));
                } else {
                    out.println("+ " + q);
                }
            }
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void genSamples() {
        writeTest(new int[]{0, 1, 0, 2, 2, 2}, new int[]{4, 5, 6, 7, -6, -5});
    }

    public int[] binaryTree(int n) {
        int[] p = new int[n - 1];
        for (int i = 1; i < n; i++) {
            p[i - 1] = (i - 1) / 2;
        }
        return p;
    }

    public int[] star(int n) {
        return new int[n - 1];
    }

    public int[] random(int n) {
        int[] p = new int[n - 1];
        for (int i = 0; i < p.length; i++) {
            p[i] = rnd.nextInt(i + 1);
        }
        return p;
    }

    public int[] vine(int n) {
        int[] p = new int[n - 1];

        int k = n / 2;
        for (int i = 0; i < k; i++) {
            p[i] = i;
        }
        for (int i = k; i < p.length; i++) {
            p[i] = i - k;
        }
        return p;
    }

    public int[] starAndTree(int n) {
        int[] p = new int[n - 1];
        int k = (int) Math.sqrt(n - 1);

        for (int i = 0; i < (n - 1) / k; i++) {
            int size = i == (n - 1) / k - 1 ? (n - 1 - i * k) : k;
            int shift = i * k;
            p[shift] = 0;
            for (int j = 1; j < size; j++) {
                p[shift + j] = shift + (j - 1) / 2;
            }
        }
        return p;
    }

    public int[] bambooAndTree(int n) {
        int[] p = new int[n - 1];
        for (int i = 0; i < n / 2; i++) {
            p[i] = i;
        }
        int shift = n / 2;
        p[shift] = shift;
        for (int i = 1; i < n - 1 - (shift + 1); i++) {
            p[shift + i] = shift + (i - 1) / 2;
        }
        return p;
    }

    public int[] starAndVine(int n) {
        int[] p = new int[n - 1];
        int k = (int) Math.sqrt(n - 1);
        for (int i = 0; i < (n - 1) / k; i++) {
            int size = i == (n - 1) / k - 1 ? (n - 1 - i * k) : k;
            int shift = i * k;
            p[shift] = 0;
            for (int j = 1; j < size / 2; j++) {
                p[shift + j] = shift + j;
            }
            for (int j = size / 2; j < size; j++) {
                p[shift + j] = shift + j - (size / 2);
            }
        }
        return p;
    }

    int[] color;
    ArrayList<Integer>[] e;

    public void dfs(int v, int c) {
        color[v] = c;
        for (int u : e[v]) {
            dfs(u, c);
        }
    }

    public ArrayList<Integer>[] leaves(int[] p) {
        color = new int[p.length + 1];
        for (int i = 0; i < color.length; i++) {
            color[i] = -1;
        }
        e = lists(p.length + 1);
        for (int i = 0; i < e.length; i++) {
            e[i] = new ArrayList<>();
        }
        for (int i = 0; i < p.length; i++) {
            e[p[i]].add(i + 1);
        }
        int c = 0;
        for (int v : e[0]) {
            dfs(v, c++);
        }
        ArrayList<Integer>[] leaves = lists(c);
        for (int i = 0; i < leaves.length; i++) {
            leaves[i] = new ArrayList<>();
        }
        for (int i = 1; i < p.length + 1; i++) {
            if (e[i].size() == 0) {
                leaves[color[i]].add(i);
            }
        }
        return leaves;
    }

    @SuppressWarnings("unchecked")
    private <T> ArrayList<T>[] lists(final int c) {
        return new ArrayList[c];
    }

    public class Pair implements Comparable<Pair> {
        int v;
        int r;

        public Pair(int v) {
            this.v = v;
            this.r = rnd.nextInt(239);
        }

        public int compareTo(Pair p) {
            return p.r == r ? v - p.v : r - p.r;
        }
    }

    public void genRandomQueries(int[] p, int nq, boolean onlyAdd) {
        ArrayList<Integer>[] leaves = leaves(p);
        @SuppressWarnings("unchecked") TreeSet<Pair>[] toAdd = new TreeSet[leaves.length];
        @SuppressWarnings("unchecked") TreeSet<Pair>[] toRemove = new TreeSet[leaves.length];
        TreeSet<Pair> hasToAdd = new TreeSet<>();
        TreeSet<Pair> hasToRemove = new TreeSet<>();

        for (int i = 0; i < leaves.length; i++) {
            toAdd[i] = new TreeSet<>();
            toRemove[i] = new TreeSet<>();
            for (int l : leaves[i]) {
                toAdd[i].add(new Pair(l));
            }
            hasToAdd.add(new Pair(i));
        }
        int[] q = new int[nq];
        for (int i = 0; i < q.length; i++) {
            if (onlyAdd && hasToAdd.size() == 0) {
                q = Arrays.copyOf(q, i);
                break;
            }
            if ((rnd.nextBoolean() || hasToRemove.size() == 0 || onlyAdd) && hasToAdd.size() != 0) {
                int subtree = hasToAdd.pollFirst().v;
                int leafAdd = toAdd[subtree].pollFirst().v;
                if (toAdd[subtree].size() != 0) {
                    hasToAdd.add(new Pair(subtree));
                }
                if (toRemove[subtree].size() == 0) {
                    hasToRemove.add(new Pair(subtree));
                }
                toRemove[subtree].add(new Pair(leafAdd));
                q[i] = leafAdd + 1;
            } else {
                int subtree = hasToRemove.pollFirst().v;
                int leafRemove = toRemove[subtree].pollFirst().v;
                if (toAdd[subtree].size() == 0) {
                    hasToAdd.add(new Pair(subtree));
                }
                if (toRemove[subtree].size() != 0) {
                    hasToRemove.add(new Pair(subtree));
                }
                toAdd[subtree].add(new Pair(leafRemove));
                q[i] = -leafRemove - 1;
            }
        }
        shuffle(p, q);
        writeTest(p, q);
    }

    public void genFlash(int[] p, int nq, boolean remove) {
        ArrayList<Integer>[] leaves = leaves(p);

        ArrayList<Integer>[] workingLeaves = lists(leaves.length);
        for (int i = 0; i < leaves.length; i++) {
            workingLeaves[i] = new ArrayList<>();
            for (int j = 0; j < Math.min(leaves[i].size() / 2, 10); j++) {
                workingLeaves[i].add(leaves[i].get(j));
            }
            for (int j = Math.max(leaves[i].size() / 2, leaves[i].size() - 10); j < leaves[i].size(); j++) {
                workingLeaves[i].add(leaves[i].get(j));
            }
        }
        int[][] inWork = new int[leaves.length][2];
        for (int i = 0; i < leaves.length; i++) {
            Arrays.fill(inWork[i], -1);
        }
        int[] q = new int[nq];
        for (int i = 0; i < q.length; i++) {
            int subtree = rnd.nextInt(leaves.length);
            int toChoose = inWork[subtree][0] == -1 ? 0 : inWork[subtree][1] == -1 ? 1 : 2;
            if (((!remove || rnd.nextDouble() < 0.6) && toChoose == 1 && leaves[subtree].size() > 2) || toChoose == 0) {
                int newLeaf;
                do {
                    if (rnd.nextDouble() < 0.8) {
                        newLeaf = workingLeaves[subtree].get(rnd.nextInt(workingLeaves[subtree].size()));
                    } else {
                        newLeaf = leaves[subtree].get(rnd.nextInt(leaves[subtree].size()));
                    }
                } while (newLeaf == inWork[subtree][0] || newLeaf == inWork[subtree][1]);
                inWork[subtree][toChoose] = newLeaf;
                q[i] = newLeaf + 1;
            } else {
                q[i] = -inWork[subtree][0] - 1;
                inWork[subtree][0] = inWork[subtree][1];
                inWork[subtree][1] = -1;
            }
        }
        shuffle(p, q);
        writeTest(p, q);
    }

    public void gen() {
        genSamples();

        genRandomQueries(binaryTree(2), 100, false);
        genRandomQueries(binaryTree(3), 100, false);
        genRandomQueries(new int[] {0, 1}, 100, false);
        genRandomQueries(new int[] {0, 1, 2}, 100, false);

        int[] sizes = new int[]{10, 100, MAX_N};
        int[] queries = new int[]{100, MAX_Q, MAX_Q};

        for (int i = 0; i < sizes.length; i++) {
            int size = sizes[i];
            int query = queries[i];

            genRandomQueries(binaryTree(size), query, false);
            genRandomQueries(binaryTree(size), query, true);

            genRandomQueries(vine(size), query, false);
            genRandomQueries(vine(size), query, true);

            genRandomQueries(bambooAndTree(size), query, false);
            genRandomQueries(bambooAndTree(size), query, true);

            genRandomQueries(star(size), query, false);
            genRandomQueries(star(size), query, true);

            genRandomQueries(starAndTree(size), query, false);
            genRandomQueries(starAndTree(size), query, true);

            genRandomQueries(starAndVine(size), query, false);
            genRandomQueries(starAndVine(size), query, true);
        }

        for (int i = 0; i < 3; i++) {
            genRandomQueries(random(MAX_N), MAX_Q, false);
            genRandomQueries(random(MAX_N), MAX_Q, true);
        }
        genFlash(binaryTree(MAX_N), MAX_Q, false);
        genFlash(binaryTree(MAX_N), MAX_Q, true);
        genFlash(vine(MAX_N), MAX_Q, false);
        genFlash(vine(MAX_N), MAX_Q, true);
        genFlash(bambooAndTree(MAX_N), MAX_Q, false);
        genFlash(bambooAndTree(MAX_N), MAX_Q, true);
        genFlash(starAndTree(MAX_N), MAX_Q, false);
        genFlash(starAndTree(MAX_N), MAX_Q, true);
        genFlash(starAndVine(MAX_N), MAX_Q, false);
        genFlash(starAndVine(MAX_N), MAX_Q, true);
        for (int i = 0; i < 3; i++) {
            genFlash(random(MAX_N), MAX_Q, false);
            genFlash(random(MAX_N), MAX_Q, true);
        }
    }
}

