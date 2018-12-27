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
/* Checker                                                        */
/*                                                                */
/* Author                Boris Minaev                             */
/******************************************************************/

import java.util.ArrayList;
import java.util.Collections;

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import ru.ifmo.testlib.Outcome.Type;

public class Check implements Checker {

	class Cell implements Comparable<Cell> {
		int x, y;

		public Cell(int x, int y) {
			super();
			this.x = x;
			this.y = y;
		}

		@Override
		public int compareTo(Cell arg0) {
			if (x != arg0.x) {
				return Integer.compare(x, arg0.x);
			}
			return Integer.compare(y, arg0.y);
		}

		@Override
		public String toString() {
			return "[" + x + ", " + y + "]";
		}

	}

	ArrayList<Cell> normalize(ArrayList<Cell> cells) {
		int minX = Integer.MAX_VALUE;
		int minY = Integer.MAX_VALUE;
		for (Cell c : cells) {
			minX = Math.min(minX, c.x);
			minY = Math.min(minY, c.y);
		}
		for (Cell c : cells) {
			c.x -= minX;
			c.y -= minY;
		}
		return cells;
	}

	ArrayList<Cell> generateCells(String s) {
		ArrayList<Cell> result = new ArrayList<>();
		int x = 0, y = 0;
		result.add(new Cell(x, y));
		for (char c : s.toCharArray()) {
			switch (c) {
			case 'u':
				x--;
				break;
			case 'd':
				x++;
				break;
			case 'l':
				y--;
				break;
			case 'r':
				y++;
				break;
			default:
				break;
			}
			result.add(new Cell(x, y));
		}
		Collections.sort(result);
		ArrayList<Cell> unique = new ArrayList<>();
		for (Cell c : result) {
			if (unique.size() == 0 || unique.get(unique.size() - 1).x != c.x
					|| unique.get(unique.size() - 1).y != c.y) {
				unique.add(c);
			}
		}
		return normalize(unique);
	}

	ArrayList<Cell> getAllCells(char[][] a) {
		ArrayList<Cell> result = new ArrayList<>();
		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < a[i].length; j++) {
				if (a[i][j] == 'X') {
					result.add(new Cell(i, j));
				}
			}
		}
		return normalize(result);
	}

	boolean equalsCells(ArrayList<Cell> left, ArrayList<Cell> right) {
		if (left.size() != right.size()) {
			return false;
		}
		for (int i = 0; i < left.size(); i++) {
			if (left.get(i).compareTo(right.get(i)) != 0) {
				return false;
			}
		}
		return true;
	}

	class Solution {
		boolean foundAnswer;
		int start, end;
		Outcome parseOutcome;

		public Solution(InStream in, TestCase t) {
			String ans = in.nextToken();
			if (ans.equals("YES")) {
				foundAnswer = true;
				start = in.nextInt() - 1;
				end = in.nextInt() - 1;
				if (start > end) {
					parseOutcome = new Outcome(Type.WA, "start > end: "
							+ (start + 1) + " > " + (end + 1));
					return;
				}
				if (start < 0 || start >= t.s.length()) {
					parseOutcome = new Outcome(Type.WA, "start is "
							+ (start + 1) + ", string length is "
							+ t.s.length());
					return;
				}
				if (end < 0 || end >= t.s.length()) {
					parseOutcome = new Outcome(Type.WA, "end is " + (end + 1)
							+ ", string length is " + t.s.length());
					return;
				}
				ArrayList<Cell> cells = generateCells(t.s.substring(start,
						end + 1));
				ArrayList<Cell> need = getAllCells(t.need);
				if (!equalsCells(cells, need)) {
					parseOutcome = new Outcome(Type.WA, "Pictures are not same");
				}
			} else {
				if (ans.equals("NO")) {
					foundAnswer = false;
					return;
				} else {
					parseOutcome = new Outcome(Type.WA,
							"Expected YES/NO, found " + ans);
					return;
				}
			}
		}
	}

	class TestCase {
		String s;
		char[][] need;

		public TestCase(InStream in) {
			int len = in.nextInt();
			in.skipLine();
			s = in.nextLine();
			int n = in.nextInt();
			int m = in.nextInt();
			need = new char[n][];
			in.skipLine();
			for (int i = 0; i < n; i++) {
				need[i] = in.nextLine().toCharArray();
			}
		}
	}

	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		TestCase t = new TestCase(inf);
		Solution user = new Solution(ouf, t);
		if (user.parseOutcome != null) {
			return user.parseOutcome;
		}
		Solution jury = new Solution(ans, t);
		if (jury.parseOutcome != null) {
			return new Outcome(Type.FAIL, jury.parseOutcome.getMessage());
		}
		if (jury.foundAnswer != user.foundAnswer) {
			if (jury.foundAnswer) {
				return new Outcome(Type.WA,
						"Jury found answer, but participant isn't");
			} else {
				return new Outcome(Type.FAIL, "Participant found answer!");
			}
		}
		return new Outcome(Type.OK, jury.foundAnswer ? "YES" : "NO");
	}
}

