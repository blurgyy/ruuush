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
/* Tests                                                          */
/*                                                                */
/* Author                Boris Minaev                             */
/******************************************************************/

import java.io.*;
import java.util.*;

/*
 * Created by Borys Minaiev 12.10.16
 */

public class Tests {
	Random rnd = new Random(123);
	final static int MAXNM = 100_000;
	final static int MAXL = 100000;

	public static void main(String[] args) {
		new Tests().gen();
	}

	public class TestCase {
		String s;
		char[][] a;

		TestCase(String s, int n, int m) {
			a = new char[n][m];
			this.s = s;
		}

		TestCase(String s, String[] data) {
			this.s = s;
			a = new char[data.length][];
			for (int i = 0; i < a.length; i++) {
				a[i] = data[i].toCharArray();
			}
		}

		public TestCase(String s, char[][] a) {
			super();
			this.s = s;
			this.a = a;
		}

		void decorate() {
			int more = Math.min(MAXL - s.length(), s.length());
			char[] newStr = new char[s.length() + more];
			int it = 0;
			String decor = " ,.";
			for (int i = 0; i < newStr.length; i++) {
				if (more == 0 || (rnd.nextBoolean() && it < s.length())) {
					newStr[i] = s.charAt(it++);
				} else {
					newStr[i] = decor.charAt(rnd.nextInt(decor.length()));
					more--;
				}
			}
			if (newStr[0] == ' ') {
				newStr[0] = "udlr".charAt(rnd.nextInt(4));
			}
			if (newStr[newStr.length - 1] == ' ') {
				newStr[newStr.length - 1] = "udlr".charAt(rnd.nextInt(4));
			}
			s = new String(newStr);
		}
	}

	int tests = 1;

	public void writeTest(TestCase tc) {
		try {
			PrintWriter out = new PrintWriter(String.format("tests/%02d",
					tests++));

			System.err.println("Writing test " + (tests - 1));

			out.println(tc.s.length());
			out.println(tc.s);
			out.println(tc.a.length + " " + tc.a[0].length);
			for (char[] ss : tc.a) {
				for (char c : ss) {
					out.print(c);
				}
				out.println();
			}
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	void genRandomTest(int n, int m, int l) {
		if (n * m == 1) {
			n++;
		}
		char[][] a = new char[n][m];
		for (int i = 0; i < n; i++) {
			Arrays.fill(a[i], '.');
		}
		int stX = rnd.nextInt(n), stY = rnd.nextInt(m);
		int realLen = 1 + rnd.nextInt(l);
		if (rnd.nextBoolean()) {
			realLen = l;
		}
		a[stX][stY] = 'X';
		String directions = "dulr";
		StringBuilder sb = new StringBuilder();
		int left = rnd.nextInt(l - realLen + 1);
		if (rnd.nextBoolean()) {
			for (int j = 0; j < left; j++) {
				sb.append(directions.charAt(rnd.nextInt(directions.length())));
			}
		}
		boolean goDir = rnd.nextBoolean();
		double p1 = rnd.nextDouble();
		double p2 = rnd.nextDouble();
		double p3 = rnd.nextDouble();
		for (int i = 0; i < realLen || sb.length() < realLen; i++) {
			int dir = rnd.nextInt(4);
			if (goDir) {
				if (rnd.nextDouble() < p1) {
					if (rnd.nextDouble() < p2) {
						dir = 0;
					} else {
						dir = 1;
					}
				} else {
					if (rnd.nextDouble() < p3) {
						dir = 2;
					} else {
						dir = 3;
					}
				}
			}
			int nx = stX, ny = stY;
			switch (dir) {
			case 0:
				nx++;
				break;
			case 1:
				nx--;
				break;
			case 2:
				ny--;
				break;
			case 3:
				ny++;
			default:
				break;
			}
			if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
				stX = nx;
				stY = ny;
				a[stX][stY] = 'X';
				sb.append(directions.charAt(dir));
			} else {
				i--;
			}
		}
		if (rnd.nextBoolean()) {
			for (int j = 0; j < l - realLen - left; j++) {
				sb.append(directions.charAt(rnd.nextInt(directions.length())));
			}
		}
		if (sb.length() > l) {
			throw new AssertionError();
		}
		int sum = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (a[i][j] == 'X') {
					sum++;
				}
			}
		}
		while (sum < 2) {
			int x = rnd.nextInt(n);
			int y = rnd.nextInt(m);
			if (a[x][y] == '.') {
				a[x][y] = 'X';
				sum++;
			}
		}
		if (rnd.nextDouble() < 0.1 && sum > 2) {
			while (true) {
				int x = rnd.nextInt(n);
				int y = rnd.nextInt(m);
				if (a[x][y] == 'X') {
					a[x][y] = '.';
					break;
				}
			}
		}
		TestCase tc = new TestCase(sb.toString(), a);
		tc.decorate();
		writeTest(tc);
	}

	void genDown(int n, int m, int l) {
		char[][] a = new char[n][m];
		for (int i = 0; i < n; i++) {
			if (i == n / 2) {
				Arrays.fill(a[i], 'X');
			} else {
				if (i < n / 2) {
					a[i][0] = 'X';
					a[i][1] = '.';
				} else {
					a[i][0] = '.';
					a[i][1] = 'X';
				}
			}
		}
		char dir = 'd';
		int pos = rnd.nextInt(l);
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < l; i++) {
			if (i == pos) {
				sb.append('r');
			} else {
				sb.append(dir);
			}
		}
		TestCase tc = new TestCase(sb.toString(), a);
		tc.decorate();
		writeTest(tc);
	}

	void genRight(int n, int m, int l) {
		char[][] a = new char[n][m];
		for (int i = 0; i < n; i++) {
			Arrays.fill(a[i], 'X');
		}
		for (int i = 0; i < m; i++) {
			if (i != m / 2) {
				if (i < m / 2) {
					a[0][i] = 'X';
					a[1][i] = '.';
				} else {
					a[0][i] = '.';
					a[1][i] = 'X';
				}
			}
		}
		char dir = 'r';
		int pos = rnd.nextInt(l);
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < l; i++) {
			if (i == pos) {
				sb.append('d');
			} else {
				sb.append(dir);
			}
		}
		TestCase tc = new TestCase(sb.toString(), a);
		tc.decorate();
		writeTest(tc);
	}

	void genOneDir(int n, int m, int l) {
		if (n != 1 && m != 1) {
			throw new AssertionError();
		}
		char[][] a = new char[n][m];
		for (int i = 0; i < n; i++) {
			Arrays.fill(a[i], 'X');
		}
		char dir = (n == 1 ? 'r' : 'd');
		int more = n * m - l;
		StringBuilder sb = new StringBuilder();
		for (int j = 0; j + 1 < more; j++) {
			sb.append(dir);
		}
		if (more > 0) {
			sb.append((char) ('r' + 'd' - dir));
		}
		for (int i = 0; i < l; i++) {
			sb.append(dir);
		}
		TestCase tc = new TestCase(sb.toString(), a);
		tc.decorate();
		writeTest(tc);
	}

	void genSpec(boolean dir) {
		int l = MAXL;
		StringBuilder sb = new StringBuilder();
		ArrayList<Integer> goodPos = new ArrayList<>();
		for (int i = 0; i < l - 5;) {
			goodPos.add(i);
			if (rnd.nextBoolean()) {
				i += 2;
				if (dir) {
					sb.append("ud");
				} else {
					sb.append("du");
				}
			}
			i++;
			sb.append('r');
		}
		char[][] res = new char[2][MAXNM / 2];
		for (int i = 0; i < res.length; i++) {
			Arrays.fill(res[i], '.');
		}
		String s = sb.toString();
		int stX = dir ? 1 : 0;
		int stY = 0;
		res[stX][stY] = 'X';
		for (int i = goodPos.get(goodPos.size() / 4); i < s.length(); i++) {
			switch (s.charAt(i)) {
			case 'u':
				stX--;
				break;
			case 'd':
				stX++;
				break;
			case 'r':
				stY++;
				break;
			default:
				throw new AssertionError();
			}
			res[stX][stY] = 'X';
		}
		TestCase tc = new TestCase(s, res);
		tc.decorate();
		writeTest(tc);
	}

	void genRandomTest(int n, int m) {
		int l = 1 + rnd.nextInt(n * m);
		if (l > MAXL) {
			l = MAXL;
		}
		genRandomTest(n, m, l);
	}

	public void genSamples() {
		writeTest(new TestCase("you should read statement really carefully.",
				new String[] { "...XX.", "..XXX.", "...XXX" }));
		writeTest(new TestCase("you should read statement really carefully.",
				new String[] { "XX", "XX", "XX" }));
		writeTest(new TestCase("you should read statement really carefully.",
				new String[] { "XX", "XX", ".X" }));
	}

	private void genMorse() {
		int len = 1 << 14;
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < len; i++) {
			if (Integer.bitCount(i) % 2 == 0) {
				sb.append("d");
			} else {
				sb.append("drl");
			}
		}
		int n = len + 1, m = 2;
		char[][] a = new char[n][m];
		a[0] = "X.".toCharArray();
		for (int i = 0; i < len; i++) {
			a[i + 1][0] = 'X';
			a[i + 1][1] = Integer.bitCount(i) % 2 == 0 ? 'X' : '.';
		}
		TestCase tc = new TestCase(sb.toString(), a);
		writeTest(tc);
	}

	private void genMorse2() {
		int len = 1 << 10;
		StringBuilder sb = new StringBuilder();
		for (int i = 0; sb.length() < MAXL; i++) {
			if (Integer.bitCount(i) % 2 == 0) {
				sb.append("d");
			} else {
				sb.append("drl");
			}
		}
		int n = 3 * len + 1, m = 2;
		char[][] a = new char[n][m];
		a[0] = "X.".toCharArray();
		int it = 1;
		for (int cnt = 0; cnt < 3; cnt++) {
			for (int i = 0; i < len; i++) {
				a[it][0] ='X';
				a[it][1] = Integer.bitCount(i) % 2 == 0 ? 'X' : '.';
				it++;
			}
		}
		TestCase tc = new TestCase(sb.toString(), a);
		writeTest(tc);
	}

	private void genMorse3() {
		int len = 1 << 10;
		StringBuilder sb = new StringBuilder();
		for (int i = 0; sb.length() + 6 * len < MAXL; i++) {
			if (Integer.bitCount(i) % 2 == 0) {
				sb.append("d");
			} else {
				sb.append("drl");
			}
		}
		for (int cnt = 0; cnt < 3; cnt++) {
			for (int i = 0; i < len; i++) {
				sb.append(Integer.bitCount(i) % 2 == 0 ? "d" : "drl");
			}
		}
		int n = 3 * len + 1, m = 2;
		char[][] a = new char[n][m];
		a[0] = "X.".toCharArray();
		int it = 1;
		for (int cnt = 0; cnt < 3; cnt++) {
			for (int i = 0; i < len; i++, it++) {
				a[it][0] = 'X';
				if (Integer.bitCount(i) % 2 == 0) {
					a[it][1] = '.';
				} else {
					a[it][1] = 'X';
				}
			}
		}
		if (it != n) {
			throw new AssertionError();	
		}
		TestCase tc = new TestCase(sb.toString(), a);
		writeTest(tc);
	}

	public void gen() {
		genSamples();

		writeTest(new TestCase("ll", new String[] { "XXX" }));

		genSpec(false);
		genSpec(true);

		for (int i = 0; i < 10; i++) {
			genRandomTest(1 + rnd.nextInt(50), 1 + rnd.nextInt(50));
		}

		for (int i = 0; i < 3; i++) {
			genDown(MAXNM / 2, 2, MAXL);
			genRight(2, MAXNM / 2, MAXL);
		}

		for (int i = 0; i < 10; i++) {
			int x = 1 + rnd.nextInt(MAXNM);
			int y = MAXNM / x;
			genRandomTest(x, y);
			genRandomTest(y, x);
		}

		genOneDir(MAXNM, 1, MAXL);
		genOneDir(MAXNM / 2, 1, MAXL);
		genOneDir(1, MAXNM, MAXL);
		genOneDir(1, MAXNM / 2, MAXL);

		genMorse();
		genMorse2();
		genMorse3();


		for (int i = 0; i < 10; i++) {
			int sq = (int) Math.sqrt(MAXNM);
			genRandomTest(sq, sq, MAXL);
		}

		for (int it = 0; it < 4; it++) {
			genRandomTest(1, MAXNM, MAXL);
			genRandomTest(MAXNM, 1, MAXL);
			genRandomTest(2, MAXNM / 2, MAXL);
			genRandomTest(MAXNM / 2, 2, MAXL);
		}

		for (int it = 0; it < 5; it++) {
			genRandomTest(10, MAXNM / 10, MAXL);
			genRandomTest(MAXNM / 10, 10, MAXL);
		}
	}
}
