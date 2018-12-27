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
/* Author                Boris Minaev                             */
/******************************************************************/

import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class easy_bm_check {
	FastScanner in;
	PrintWriter out;

	long[] genPowers(long p, int cnt) {
		long[] result = new long[cnt];
		result[0] = 1;
		for (int i = 1; i < result.length; i++) {
			result[i] = result[i - 1] * p;
		}
		return result;
	}

	long[] powX, powY;

	class Cell {
		int x, y;
		long hash;

		public Cell(int x, int y) {
			super();
			this.x = x;
			this.y = y;
			hash = powX[x] * powY[y];
		}

		public int hashCode() {
			return (int) hash;
		}

		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Cell other = (Cell) obj;
			if (!getOuterType().equals(other.getOuterType()))
				return false;
			if (hash != other.hash)
				return false;
			if (x != other.x)
				return false;
			if (y != other.y)
				return false;
			return true;
		}

		private easy_bm_check getOuterType() {
			return easy_bm_check.this;
		}

		@Override
		public String toString() {
			return "Cell [x=" + x + ", y=" + y + ", hash=" + hash + "]";
		}

	}

	void solve() throws IOException {
		int l = in.nextInt();
		String s = in.br.readLine();
		int n = in.nextInt();
		int m = in.nextInt();
		char[][] a = new char[n][];
		for (int i = 0; i < n; i++) {
			a[i] = in.next().toCharArray();
		}
		int cnt = 0, minX = n, minY = m;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (a[i][j] == 'X') {
					cnt++;
					minX = Math.min(minX, i);
					minY = Math.min(minY, j);
				}
			}
		}
		if (cnt == 0) {
			throw new AssertionError();
		}
		Random rnd = new Random(123);
		int sz = Math.max(l * 2, Math.max(n, m)) + 5;
		powX = genPowers(BigInteger.valueOf(100000000 + rnd.nextInt(100000000))
				.nextProbablePrime().intValue(), sz);
		powY = genPowers(BigInteger.valueOf(100000000 + rnd.nextInt(100000000))
				.nextProbablePrime().intValue(), sz);
		long needHash = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (a[i][j] == 'X') {
					needHash += new Cell(i - minX, j - minY).hash;
				}
			}
		}
		int curX = l + 3, curY = l + 3;
		Cell[] cells = new Cell[l + 1];
		cells[0] = new Cell(curX, curY);
		for (int i = 0; i < l; i++) {
			switch (s.charAt(i)) {
			case 'u':
				curX--;
				break;
			case 'd':
				curX++;
				break;
			case 'l':
				curY--;
				break;
			case 'r':
				curY++;
				break;
			default:

			}
			cells[i + 1] = new Cell(curX, curY);
		}
		int left = 0;
		HashMap<Cell, Integer> count = new HashMap();
		int curCnt = 0;
		long nowHash = 0;
		Comparator<Cell> xComp = new Comparator<easy_bm_check.Cell>() {

			public int compare(Cell arg0, Cell arg1) {
				if (arg0.x != arg1.x) {
					return Integer.compare(arg0.x, arg1.x);
				}
				return Integer.compare(arg0.y, arg1.y);
			}
		};
		Comparator<Cell> yComp = new Comparator<easy_bm_check.Cell>() {
			public int compare(Cell arg0, Cell arg1) {
				if (arg0.y != arg1.y) {
					return Integer.compare(arg0.y, arg1.y);
				}
				return Integer.compare(arg0.x, arg1.x);
			}
		};
		TreeSet<Cell> xCell = new TreeSet<Cell>(xComp);
		TreeSet<Cell> yCell = new TreeSet<Cell>(yComp);
		for (int right = 0; right <= l; right++) {
			Integer now = count.get(cells[right]);
			if (now == null || now == 0) {
				now = 0;
				curCnt++;
				nowHash += cells[right].hash;
				xCell.add(cells[right]);
				yCell.add(cells[right]);
			}
			count.put(cells[right], now + 1);
			while (curCnt > cnt) {
				Integer was = count.get(cells[left]);
				if (was - 1 == 0) {
					curCnt--;
					nowHash -= cells[left].hash;
					xCell.remove(cells[left]);
					yCell.remove(cells[left]);
				}
				count.put(cells[left], was - 1);
				left++;
			}
			if (curCnt == cnt) {
				int curMinX = xCell.first().x;
				int curMinY = yCell.first().y;
				if (nowHash == needHash * powX[curMinX] * powY[curMinY]) {
					boolean ok = true;
					for (Cell c : xCell) {
						if (c.x - curMinX + minX >= a.length
								|| c.y - curMinY + minY >= a[0].length
								|| a[c.x - curMinX + minX][c.y - curMinY + minY] == '.') {
							ok = false;
							break;
						}
					}
					if (ok) {
						out.println("YES");
						out.println((left + 1) + " " + (right));
						return;
					}
				}
			}
		}
		out.println("NO");
	}

	void run() {
		try {
			in = new FastScanner(new File("easy.in"));
			out = new PrintWriter(new File("easy.out"));

			solve();

			out.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
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
		new easy_bm_check().run();
	}
}
