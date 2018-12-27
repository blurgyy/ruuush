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
/* Tests                                                          */
/*                                                                */
/* Author                Mikhail Dvorkin                          */
/******************************************************************/

import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Tests {
	public static final boolean ACCURATE = true;
	private static File dir = new File("tests");
	private int curTest = 1;
	private static boolean verbose = true;

	private String testName;
	private PrintWriter out;
	private Random r = new Random(5516681322906813814L);
	public static final int MAX_WIDTH = 100;
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

	public void run() {
		t(true, "37", "34");
		t(true, "2", "2");
		t(false, "6", "0", "1");
		for (int i = 0; i < 2; i++) {
			tSegments(false, "1", "11", "0", "11", "" + i, "11", "0", "11", "1");
		}
		tSegments(false, "0", "11", "1", "01", "0", "11", "1", "01", "0");
		t(true, "1", "1");
		t(true, "0", "1");
		t(false, "1", "3", "3");
		t(true, "4", "5");
		t(false, "4", "3", "8");
		t(true, "1", "8");
		for (int mask = 0; mask < 8; mask++) {
			String a = "" + (mask & 1);
			String b = "" + ((mask >> 1) & 1) + ((mask >> 2) & 1);
			tSegments(null, a, b, a, b, a, b, a, b, a);
		}
		t(true, "239", "566");
		t(false, "000", "111", "000");
		t(true, "566", "239");
		t(false, "11", "11", "88");
		t(true, "000", "000");
		t(true, "1", "999");
		t(true, "777", "777");
		if (MAX_WIDTH >= 10) {
			t(true, "" + r.nextInt(Integer.MAX_VALUE), "" + r.nextInt(Integer.MAX_VALUE));
		}
		t(true, randomNumber(MAX_WIDTH / 3), randomNumber(MAX_WIDTH / 3));
		for (int w : new int[]{(int) Math.sqrt(MAX_WIDTH), MAX_WIDTH - 1, MAX_WIDTH}){
			for (int shift = -1; shift <= 1; shift += 2) {
				for (;;) {
					String a = randomNumber(w);
					String b = randomNumber(w);
					String c = new BigInteger(a).add(new BigInteger(b)).add(BigInteger.valueOf(shift)).toString();
					boolean[][] p = genPicture(a, b, c);
					if (solve(p)) {
						continue;
					}
					t(false, p);
					break;
				}
			}
		}
		if (MAX_WIDTH >= 100) {
			StringBuilder[] sb = new StringBuilder[6];
			for (int i = 0; i < sb.length; i++) {
				sb[i] = new StringBuilder();
			}
			for (int i = 0; i < 100; i++) {
				int p = i / 10;
				int q = i % 10;
				sb[0].append(p);
				sb[1].append(q);
				sb[2].append(9 - p);
				sb[3].append(9 - q);
				if (i % 3 == 1) {
					sb[4].append(randomNumber(1));
					sb[5].append(randomNumber(1));
				} else {
					sb[4].append(1);
					sb[5].append(1);
				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < i; j++) {
					t(true, sb[i].toString(), sb[j].toString());
					t(null, sb[i].toString(), sb[j].toString(), "");
				}
			}
			t(true, sb[4].toString(), sb[5].toString());
		}
		{
			boolean[][] picture = new boolean[9][MAX_WIDTH + 1];
			t(false, picture);
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 1 + i % 2; j++) {
					picture[i][j] = picture[i][MAX_WIDTH - 1 + j] = true;
				}
			}
			t(false, picture);
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j <= MAX_WIDTH; j++) {
					picture[i][j] = r.nextBoolean();
				}
			}
			t(false, picture);
			for (int i = 0; i < 9; i++) {
				if (i == 2 || i == 4 || i == 6) {
					continue;
				}
				for (int j = 0; j <= MAX_WIDTH; j++) {
					picture[i][j] = true;
				}
			}
			Arrays.fill(picture[6], true);
			t(null, picture);
			Arrays.fill(picture[4], true);
			t(null, picture);
			Arrays.fill(picture[2], true);
			t(null, picture);
		}
		System.out.println("Long calculations are coming...");
		for (int w : new int[]{1, 2, Math.min(4, MAX_WIDTH), (int) Math.sqrt(MAX_WIDTH), MAX_WIDTH - 1}) {
			t(true, genMinimalTrue(w));
		}
		{
			boolean[][] picture = genMinimalTrue(MAX_WIDTH);
			t(true, picture);
			iloop:
			for (int i = 0; i < 9; i++) {
				int j;
				for (int k = 0;; k++) {
					j = r.nextInt(picture[1].length);
					if (picture[i][j]) {
						break;
					}
					if (k == 2 * MAX_WIDTH) {
						continue iloop;
					}
				}
				picture[i][j] = false;
				t(false, picture);
				picture[i][j] = true;
				int seen = 0;
				for (int tries = 0; tries < 2 * MAX_WIDTH && seen != 3; tries++) {
					for (int k = 0;; k++) {
						j = r.nextInt(picture[1].length - 1);
						if (!picture[i][j]) {
							break;
						}
						if (k == 2 * MAX_WIDTH) {
							continue iloop;
						}
					}
					picture[i][j] = true;
					int result = solve(picture) ? 1 : 0;
					if (((seen >> result) & 1) == 0) {
						t(result > 0, picture);
						seen |= 1 << result;
					}
					picture[i][j] = false;
				}
			}
		}
		for (int w : new int[]{1, MAX_WIDTH * 3 / 4, MAX_WIDTH}) {
			int seen = 0;
			for (; seen != 3;) {
				BigInteger a = new BigInteger(randomNumber(w));
				BigInteger b = new BigInteger(randomNumber(w));
				BigInteger c = a.add(b);
				if (c.toString().length() <= w) {
					continue;
				}
				boolean[][] picture = genPicture(a.toString(), b.toString(), c.toString().substring(1));
				int result = solve(picture) ? 1 : 0;
				if (((seen >> result) & 1) == 0) {
					t(result > 0, picture);
					seen |= 1 << result;
				}
			}
		}
	}

	boolean[][] genMinimalTrue(int w) {
		boolean[][] picture = new boolean[9][w + 1];
		for (int i = 0; i < 9; i++) {
			Arrays.fill(picture[i], true);
			if (i % 2 == 0) {
				picture[i][w] = false;
			}
		}
		main:
		for (;;) {
			for (int tries = 0; tries < 2 * 9 * (w + 1); tries++) {
				int i, j;
				do {
					i = r.nextInt(9);
					j = r.nextInt(w + 1);
				} while (!picture[i][j]);
				picture[i][j] = false;
				if (solve(picture)) {
					continue main;
				}
				picture[i][j] = true;
			}
			break;
		}
		return picture;
	}

	String randomNumber(int w) {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < w; i++) {
			sb.append(r.nextInt(10));
		}
		return sb.toString();
	}

	void t(Boolean expected, String a, String b) {
		t(expected, new String[]{a, b, "" + new BigInteger(a).add(new BigInteger(b))});
	}

	void t(Boolean expected, String... d) {
		t(expected, genPicture(d));
	}

	static boolean[][] genPicture(String... d) {
		int w = Math.max(Math.max(d[0].length(), d[1].length()), d[2].length());
		if (w > MAX_WIDTH) {
			d[2] = d[2].substring(1);
			w = Math.max(Math.max(d[0].length(), d[1].length()), d[2].length());
		}
		for (int i = 0; i < 3; i++) {
			while (d[i].length() < w) {
				d[i] = "0" + d[i];
			}
		}
		boolean[][] picture = new boolean[9][w + 1];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < w; j++) {
				String digit = DIGITAL[d[i].charAt(j) - '0'];
				picture[2 * i][j] |= digit.charAt(0) == '+';
				picture[2 * i + 1][j] |= digit.charAt(1) == '+';
				picture[2 * i + 1][j + 1] |= digit.charAt(2) == '+';
				picture[2 * i + 2][j] |= digit.charAt(3) == '+';
				picture[2 * i + 3][j] |= digit.charAt(4) == '+';
				picture[2 * i + 3][j + 1] |= digit.charAt(5) == '+';
				picture[2 * i + 4][j] |= digit.charAt(6) == '+';
			}
		}
		return picture;
	}

	void tSegments(Boolean expected, String... table) {
		boolean[][] picture = new boolean[9][];
		for (int i = 0; i < 9; i++) {
			picture[i] = new boolean[table[i].length()];
			for (int j = 0; j < picture[i].length; j++) {
				picture[i][j] = table[i].charAt(j) == '1';
			}
		}
		t(expected, picture);
	}

	void t(Boolean expected, boolean[][] picture) {
		int w = picture[1].length - 1;
		if (w > MAX_WIDTH) {
			throw new RuntimeException("Too wide");
		}
		open();
		System.out.print(" w=" + w + ".");
		if (ACCURATE && expected != null) {
			if (solve(picture) != expected) {
				throw new RuntimeException("Unexpected answer for " + Arrays.deepToString(picture));
			}
			System.out.print(" Answer is " + (expected ? "YES" : "NO") + ".");
		}
		out.println(w);
		for (int i = 0; i < 9; i++) {
			int len = w + i % 2;
			for (int j = 0; j < len; j++) {
				if (i % 2 == 0 || j > 0) {
					out.print(" ");
				}
				out.print(picture[i][j] ? 1 : 0);
			}
			out.println();
		}
		close();
	}

	private void open() {
		try {
			testName = "" + curTest / 10 + curTest % 10;
			out = new PrintWriter(new File(dir, testName));
			if (verbose) { 
				System.out.print("Generating " + testName + "...");
			}
		} catch (IOException e) {
			throw new RuntimeException("Unable to open " + testName + " for writing", e);
		}
	}

	private void close() {
		out.close();
		if (verbose) {
			System.out.println(" Done.");
		}
		curTest++;
	}

	static boolean solve(boolean[][] picture) {
		int w = picture[1].length - 1;
		int MASKS = 32;
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
		return a[0][mask] != -1;
	}

	public static void main(String[] args) {
		Locale.setDefault(Locale.US);
		dir.mkdirs();
		new Tests().run();
	}
}

