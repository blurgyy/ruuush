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
/* Solution                                                       */
/*                                                                */
/* Author                Pavel Mavrin                             */
/******************************************************************/

import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class boysgirls_pm {
	FastScanner in;
	PrintWriter out;

	boolean build(char[] res, int start, int x, int y, int z) {
		// System.out.println("build " + start + " "  + x + " " + y + " " + z);
		int n = x + y + z;
		int c = start;
		if (z == 0) {
			if (x == 0) {
				for (int i = 0; i < n; i++) {
					res[c] = 'G';
					c = (c + 2) % res.length;
				}
			} else if (y == 0) {
				for (int i = 0; i < n; i++) {
					res[c] = 'B';
					c = (c + 2) % res.length;
				}
			} else {
				out.println("Impossible");
				return false;
			}
		} else {
			for (int i = 0; i < x; i++) {
				res[c] = 'B';
				c = (c + 2) % res.length;
			}
			for (int i = 0; i < y + 1; i++) {
				res[c] = 'G';
				c = (c + 2) % res.length;
			}
			for (int i = 0; i < z - 1; i++) {
				res[c] = i % 2 == 0 ? 'B' : 'G';
				c = (c + 2) % res.length;
			}
		}			
		return true;
	}


	void solve() {
		int n = in.nextInt();
		int x = in.nextInt();
		int y = in.nextInt();
		if (x + y < n) {
			out.println("Impossible");
			return;
		}

		int zz = x + y - n;
		if (zz % 2 == 1) {
			out.println("Impossible");
			return;
		}
		int xx = x - zz;
		int yy = y - zz;
		if (xx < 0 || yy < 0) {
			out.println("Impossible");
			return;
		}

		char[] res = new char[n];
		Arrays.fill(res, '.');
		if (n % 2 == 1) {
			if (!build(res, 0, xx, yy, zz))
				return;
		} else {
			if (zz == 0) {
				if (xx == 0) {
					Arrays.fill(res, 'G');
				} else if (yy == 0) {
					Arrays.fill(res, 'B');
				} else if (xx == yy) {
					for (int i = 0; i < n; i++) {
						res[i] = i % 2 == 0 ? 'B' : 'G';
					}
				} else {
					out.println("Impossible");
					return;
				}
			} else if (zz == 2) {
				if (xx < yy) {
					if (!build(res, 0, xx, (yy - xx - 2) / 2, 2)) {
						throw new RuntimeException();
					}
					if (!build(res, 1, 0, yy - (yy - xx - 2) / 2, 0)) {
						throw new RuntimeException();
					}
				} else if (xx > yy) {
					if (!build(res, 0, (xx - yy - 2) / 2, yy, 2)) {
						throw new RuntimeException();
					}
					if (!build(res, 1, xx - (xx - yy - 2) / 2, 0, 0)) {
						throw new RuntimeException();
					}
				} else {
					out.println("Impossible");
					return;
				}
			} else {
				if (xx == 0 && yy == 0 && zz % 4 == 2) {
					out.println("Impossible");
					return;
				}
				int z1 = 2;
				int x1 = Math.min(xx, n / 2 - z1);
				int y1 = Math.min(yy, n / 2 - z1 - x1);
				z1 += n / 2 - x1 - y1 - z1;
				if (z1 % 2 == 1) {
					if (x1 > 0) {
						x1--;
					} else {
						y1--;
					}
					z1++;
				}
				int z2 = zz - z1;
				int x2 = xx - x1;
				int y2 = yy - y1;
				if (!build(res, 0, x1, y1, z1)) {
					throw new RuntimeException();
				}
				if (!build(res, 1, x2, y2, z2)) {
					throw new RuntimeException();
				}
			}
		}
		out.println(new String(res));
	}

	void run() {
		try {
			in = new FastScanner(new File("boysgirls.in"));
			out = new PrintWriter(new File("boysgirls.out"));

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
		new boysgirls_pm().run();
	}
}
