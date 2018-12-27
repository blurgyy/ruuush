/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem C. CodeCoder vs TopForces                              */
/*                                                                */
/* Original idea         Egor Kulikov                             */
/* Problem statement     Egor Kulikov                             */
/* Test set              Egor Kulikov                             */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Boris Minaev                             */
/******************************************************************/

import java.io.*;
import java.util.*;

public class codecoder_bm {
	FastScanner in;
	PrintWriter out;

	class Coder {
		int id;
		int tc;
		int ans;

		@Override
		public String toString() {
			return "Coder [id=" + id + ", tc=" + tc + ", cf=" + cf + "]";
		}

		boolean was;
		int cf;
		ArrayList<Coder> edges;

		public Coder(int id, int tc, int cf) {
			this.id = id;
			this.tc = tc;
			this.cf = cf;
			edges = new ArrayList<>();
		}

	}

	void go(Coder c, ArrayList<Coder> res) {
		c.was = true;
		res.add(c);
		for (Coder e : c.edges) {
			if (!e.was) {
				go(e, res);
			}
		}
	}

	void solve() {
		int n = in.nextInt();
		Coder[] a = new Coder[n];
		for (int i = 0; i < n; i++) {
			a[i] = new Coder(i, in.nextInt(), in.nextInt());
		}
		Comparator<Coder> cfCmp = new Comparator<Coder>() {
			@Override
			public int compare(Coder arg0, Coder arg1) {
				return Integer.compare(arg0.cf, arg1.cf);
			}
		};
		Comparator<Coder> tcCmp = new Comparator<Coder>() {
			@Override
			public int compare(Coder arg0, Coder arg1) {
				return Integer.compare(arg0.tc, arg1.tc);
			}
		};
		Comparator<Coder> idCmp = new Comparator<Coder>() {
			@Override
			public int compare(Coder arg0, Coder arg1) {
				return Integer.compare(arg0.id, arg1.id);
			}
		};
		Arrays.sort(a, cfCmp);
		for (int i = 1; i < n; i++) {
			a[i].edges.add(a[i - 1]);
		}
		Arrays.sort(a, tcCmp);
		for (int i = 1; i < n; i++) {
			a[i].edges.add(a[i - 1]);
		}
		int sz = 0;
		for (int i = 0; i < n; i++) {
			if (a[i].was) {
				continue;
			}
			ArrayList<Coder> result = new ArrayList<>();
			go(a[i], result);
			sz += result.size();
			for (Coder c : result) {
				c.ans = sz;
			}
		}
		Arrays.sort(a, idCmp);
		for (Coder c : a) {
			out.println(c.ans - 1);
		}
	}

	void run() {
		try {
			in = new FastScanner(new File("codecoder.in"));
			out = new PrintWriter(new File("codecoder.out"));

			solve();

			out.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	void runIO() {

		in = new FastScanner(System.in);
		out = new PrintWriter(System.out);

		solve();

		out.close();
	}

	class FastScanner {
		BufferedReader br;
		StringTokenizer st;

		public FastScanner(File f) {
			try {
				br = new BufferedReader(new FileReader(f));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}

		public FastScanner(InputStream f) {
			br = new BufferedReader(new InputStreamReader(f));
		}

		String next() {
			while (st == null || !st.hasMoreTokens()) {
				String s = null;
				try {
					s = br.readLine();
				} catch (IOException e) {
					e.printStackTrace();
				}
				if (s == null)
					return null;
				st = new StringTokenizer(s);
			}
			return st.nextToken();
		}

		boolean hasMoreTokens() {
			while (st == null || !st.hasMoreTokens()) {
				String s = null;
				try {
					s = br.readLine();
				} catch (IOException e) {
					e.printStackTrace();
				}
				if (s == null)
					return false;
				st = new StringTokenizer(s);
			}
			return true;
		}

		int nextInt() {
			return Integer.parseInt(next());
		}

		long nextLong() {
			return Long.parseLong(next());
		}

		double nextDouble() {
			return Double.parseDouble(next());
		}
	}

	public static void main(String[] args) {
		new codecoder_bm().run();
	}
}
