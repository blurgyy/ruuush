/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem D. Digital Addition                                    */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Mikhail Dvorkin                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Mikhail Dvorkin                          */
/******************************************************************/

import java.io.*;
import java.util.*;

public class digital_md {
	public static final String NO = "NO";
	public static final String[] DIGITAL = new String[]{
			"+++ +++",
			"  +  + ",
			"+ +++ +",
			"+ ++ ++",
			" +++ + ",
			"++ + ++",
			"++ ++++",
			"+ +  + ",
			"+++++++",
			"++++ ++",
	};
	public static final int MASKS = 32;

	static void run() {
		int w = in.nextInt();
		boolean[][] picture = new boolean[9][w + 1];
		for (int i = 0; i < 9; i++) {
			int len = w + i % 2;
			for (int j = 0; j < len; j++) {
				picture[i][j] = in.nextInt() > 0;
			}
		}
		int[][] a = new int[w + 1][MASKS];
		for (int i = 0; i <= w; i++) {
			Arrays.fill(a[i], -1);
		}
		a[w][0] = 0;
		boolean[][] local = new boolean[9][2];
		int[] d = new int[3];
		for (int i = w - 1; i >= 0; i--) {
			for (int mask = 0; mask < MASKS; mask++) {
				if (a[i + 1][mask] < 0) {
					continue;
				}
				int carry = (mask >> 4) & 1;
				for (d[0] = 0; d[0] < 10; d[0]++) {
					digitLoop:
					for (d[1] = 0; d[1] < 10; d[1]++) {
						d[2] = d[0] + d[1] + carry;
						int maskNext = (d[2] / 10) << 4;
						d[2] %= 10;
						for (int k = 0; k < 9; k++) {
							Arrays.fill(local[k], false);
						}
						for (int k = 0; k < 4; k++) {
							local[2 * k + 1][1] = ((mask >> k) & 1) > 0;
						}
						for (int k = 0; k < 3; k++) {
							String digit = DIGITAL[d[k]];
							local[2 * k][0] |= digit.charAt(0) == '+';
							local[2 * k + 1][0] |= digit.charAt(1) == '+';
							local[2 * k + 1][1] |= digit.charAt(2) == '+';
							local[2 * k + 2][0] |= digit.charAt(3) == '+';
							local[2 * k + 3][0] |= digit.charAt(4) == '+';
							local[2 * k + 3][1] |= digit.charAt(5) == '+';
							local[2 * k + 4][0] |= digit.charAt(6) == '+';
						}
						for (int k = 0; k < 9; k++) {
							int j = k % 2;
							if (local[k][j] ^ picture[k][i + j]) {
								continue digitLoop;
							}
						}
						for (int k = 0; k < 4; k++) {
							if (local[2 * k + 1][0]) {
								maskNext |= 1 << k;
							}
						}
						a[i][maskNext] = mask * 1000 + d[0] * 100 + d[1] * 10 + d[2];
					}
				}
			}
		}
		int mask = 0;
		for (int k = 0; k < 4; k++) {
			if (picture[2 * k + 1][0]) {
				mask |= 1 << k;
			}
		}
		if (a[0][mask] == -1) {
			out.println(NO);
			return;
		}
		StringBuilder[] ans = new StringBuilder[3];
		for (int i = 0; i < 3; i++) {
			ans[i] = new StringBuilder();
		}
		for (int i = 0; i < w; i++) {
			ans[2].append(a[i][mask] % 10);
			ans[1].append(a[i][mask] / 10 % 10);
			ans[0].append(a[i][mask] / 100 % 10);
			mask = a[i][mask] / 1000;
		}
		for (int i = 0; i < 3; i++) {
			out.println(ans[i]);
		}
	}

	static MyScanner in;
	static PrintWriter out;

	public static void main(String[] args) throws IOException {
		boolean stdStreams = false;
		String fileName = digital_md.class.getSimpleName().replaceFirst("_.*", "").toLowerCase();
		String inputFileName = fileName + ".in";
		String outputFileName = fileName + ".out";

		Locale.setDefault(Locale.US);
		BufferedReader br;
		if (stdStreams) {
			br = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);
		} else {
			br = new BufferedReader(new FileReader(inputFileName));
			out = new PrintWriter(outputFileName);
		}
		in = new MyScanner(br);
		int tests = 1;//in.nextInt();
		for (int test = 0; test < tests; test++) {
			digital_md.run();
		}
		br.close();
		out.close();
	}

	static class MyScanner {
		BufferedReader br;
		StringTokenizer st;

		MyScanner(BufferedReader br) {
			this.br = br;
		}

		void findToken() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
		}

		String next() {
			findToken();
			return st.nextToken();
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
}

