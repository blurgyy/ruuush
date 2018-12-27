// Solution to Word Search
// Author: Kevin Buchin

// Time complexity: O(n*h*w*wordlength)
// Memory: O(h*w)

// @EXPECTED_RESULTS@: CORRECT

// port of one of Thomas Beuman's c++ codes

import java.util.Scanner;
import java.util.Arrays;

public class kevin {

	private static final int hmax = 32;
	private static final int wmax = 32;
	private static final int lmax = 32;

	public static void main(String[] args)
	{
		char[][] Grid = new char[hmax][wmax + 1];
		String Word = new String(new char[lmax + 1]);

		boolean[][] Marked = new boolean[hmax][wmax];
		int[] di = {-1,-1,-1,0,0,1,1,1};
		int[] dj = {-1,0,1,-1,1,-1,0,1};
	
		int runs, run, n, h, w, d, i, j, k, m, s, i2, j2, solutions;
		boolean nosolution, ambiguous, palindrome, empty;
	
		Scanner in = new Scanner(System.in);
		
		runs = in.nextInt();
		
		for (run = 0; run < runs; run++)
		{
			// Read input
			n = in.nextInt();
			h = in.nextInt();
			w = in.nextInt();
			
			for (i = 0; i < h; i++)
			{
				String tmps = in.next();
				for (j = 0; j < w; j++)	Grid[i][j] = tmps.charAt(j);
			}

			for (boolean[] row: Marked) Arrays.fill(row, false);

			nosolution = ambiguous = false;

			// Process the words
			for (s = 0; s < n; s++)
			{
				Word = in.next();
				m = Word.length();
				// Check if palindrome
				for (k = 0; k < (m - 1) / 2 && Word.charAt(k) == Word.charAt(m - 1 - k); k++)
				{
					;
				}
				palindrome = (k == (m - 1) / 2);
				solutions = 0;

				// Try all starting positions and directions
				for (i = 0; i < h; i++)
				{
					for (j = 0; j < w; j++)
					{
						for (d = 0; d < 8; d++)
						{
							for (k = 0; k < m; k++)
							{
								i2 = i + k * di[d];
								j2 = j + k * dj[d];
								if (i2 < 0 || i2 >= h || j2 < 0 || j2 >= w || Grid[i2][j2] != Word.charAt(k))
									break;
							}
							if (k == m) // Word found
							{
								for (k = 0; k < m; k++)
								{
									Marked[i + k * di[d]][j + k * dj[d]] = true;
								}
								solutions++;
							}
						}
					}
				}
				if (solutions == 0)
				{
					nosolution = true;
				}
				if (!(solutions == 1 || (palindrome && solutions == 2) || (m == 1 && solutions == 8)))
				{
					ambiguous = true;
				}
			}

			// Print answer
			if (nosolution)
			{
				System.out.print("no solution\n");
			}
			else if (ambiguous)
			{
				System.out.print("ambiguous\n");
			}
			else
			{ // Print unmarked letters
				empty = true;
				for (i = 0; i < h; i++)
				{
					for (j = 0; j < w; j++)
					{
						if (!Marked[i][j])
						{
							System.out.print(Grid[i][j]);
							empty = false;
						}
					}
				}
				if (empty)
				{
					System.out.print("empty solution");
				}
				System.out.print("\n");
			}
		}
	}

}