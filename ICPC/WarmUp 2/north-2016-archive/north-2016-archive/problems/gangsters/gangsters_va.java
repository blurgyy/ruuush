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
/* Author                Vitaly Aksenov                           */
/******************************************************************/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * Created by Aksenov239 on 02.10.2016.
 */
public class gangsters_va {
    public static void main(String[] args) {
        new gangsters_va().run();
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    int[][] up;

    public int log2(int n) {
        int p = 1;
        int k = 0;
        while (p < n) {
            p *= 2;
            k++;
        }
        return k;
    }

    ArrayList<Integer>[] e;
    int[] tin, tout, size;
    int time = 0;

    public void dfs(int v) {
        if (tin[v] != 0) {
            return;
        }
        tin[v] = ++time;
        for (int u : e[v]) {
            dfs(u);
            size[v] += size[u];
        }
        if (size[v] == 0) {
            size[v] = 1;
        }
        tout[v] = ++time;
    }

    public boolean ancestor(int a, int v) {
        return tin[a] <= tin[v] && tout[v] <= tout[a];
    }

    public int lca(int u, int v) {
        if (u == v) {
            return u;
        }
        for (int i = up[u].length - 1; i >= 0; i--) {
            if (!ancestor(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }

    public int rootChild(int u) {
        for (int i = up[u].length - 1; i >= 0; i--) {
            if (up[u][i] != 0) {
                u = up[u][i];
            }
        }
        return u;
    }

    public class Pair {
        int min, max;

        public Pair(int min, int max) {
            this.min = min;
            this.max = max;
        }

        public Pair apply(Pair x) {
            if (min == Integer.MAX_VALUE) {
                return new Pair(x.min, x.max);
            }
            if (x.min == Integer.MAX_VALUE) {
                return new Pair(min, max);
            }
            int l = tin[min] < tin[x.min] ? min : x.min;
            int r = tout[max] > tout[x.max] ? max : x.max;
            return new Pair(l, r);
        }
    }

    Pair[] tree;
    final Pair INF = new Pair(Integer.MAX_VALUE, Integer.MIN_VALUE);

    public Pair get(int v, int a, int b, int l, int r) {
        if (b <= l || r <= a) {
            return INF;
        }
        if (a <= l && r <= b) {
            return tree[v];
        }
        return get(2 * v, a, b, l, (l + r) / 2).apply(get(2 * v + 1, a, b, (l + r) / 2, r));
    }

    public void set(int v, int x, int p, int l, int r) {
        if (l + 1 == r) {
            tree[v] = x == -1 ? INF : new Pair(x, x);
            return;
        }
        if (p < (l + r) / 2) {
            set(2 * v, x, p, l, (l + r) / 2);
            tree[v] = tree[2 * v].apply(tree[2 * v + 1]);
        } else {
            set(2 * v + 1, x, p, (l + r) / 2, r);
            tree[v] = tree[2 * v].apply(tree[2 * v + 1]);
        }
    }

    public void solve() throws IOException {
        int n = nextInt();
        int q = nextInt();
        int[] p = new int[n];
        e = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            e[i] = new ArrayList<>();
        }
        p[0] = 0;
        for (int i = 1; i < n; i++) {
            p[i] = nextInt() - 1;
            e[p[i]].add(i);
        }
        up = new int[n][log2(n) + 1];
        for (int i = 0; i < n; i++) {
            up[i][0] = p[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < up[i].length; j++) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }

        tin = new int[n];
        tout = new int[n];
        size = new int[n];
        dfs(0);

        tree = new Pair[4 * time + 1];
        for (int i = 0; i < 4 * time; i++) {
            tree[i] = INF;
        }

        int[] covered = new int[n];
        int totalCovered = 0;
        int edges = 0;
        int gangsters = 0;
        for (int i = 0; i < q; i++) {
            boolean remove = nextToken().equals("-");
            int v = nextInt() - 1;
            int u = rootChild(v);
            set(1, remove ? -1 : v, tin[v], 1, time + 1);
            Pair seg = get(1, tin[u], tout[u], 1, time + 1);
            int newCovered = 0;
            if (seg.min != Integer.MAX_VALUE) {
                newCovered = size[lca(seg.min, seg.max)];
            }
            if (covered[u] == 0) {
                edges++;
            }
            if (newCovered == 0) {
                edges--;
            }
            totalCovered += newCovered - covered[u];
            covered[u] = newCovered;
            gangsters = gangsters + (remove ? -1 : 1);
            out.println(edges + " " + (totalCovered - gangsters));
        }
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("gangsters.in"));
            out = new PrintWriter("gangsters.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

