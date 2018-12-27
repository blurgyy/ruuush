// Solution to Pawns
// Author: Kevin Buchin, java port of solution by Thomas Beuman

// Time complexity: O(n*m)
// Memory: O(n*m)

// @EXPECTED_RESULTS@: CORRECT

import java.util.Scanner;

public class kevin {

	private static final int nmax = 20;
	private static final int mmax = 20;

	public static void main(String[] args)
	{
		char[][] Board = new char[nmax][mmax + 1];
		
		int runs, run, n, m, i, j, b, w, nrmoves, whitejokers, blackjokers, doublejokers;
		
		Scanner in = new Scanner(System.in);
		
		runs = in.nextInt();
		
		for (run = 0; run < runs; run++)
		{
			// Read input
			n = in.nextInt();
			m = in.nextInt();
			
			for (i = 0; i < n; i++)
			{
				String tmps = in.next();
				for (j = 0; j < m; j++)	Board[n - 1 - i][j] = tmps.charAt(j);
			}
			nrmoves = whitejokers = blackjokers = doublejokers = 0;

			// Traverse the columns
			for (j = 0; j < m; j++)
			{
				// Find pawns
				for (i = 0; Board[i][j] != 'W'; i++)
				{
					;
				}
				w = i;
				for (i++; Board[i][j] != 'B'; i++)
				{
					;
				}
				b = i;

				if (w == 0 && b == n - 1 && n > 3) // Both pawns on their first rank (n>3)
				{
					doublejokers++;
				}
				else
				{
					if (w == 0 && b > 2)
					{
						whitejokers += b - 2; // Number of moves needed to neutralize White's joker
					}
					else if (b == n - 1 && w < n - 3)
					{
						blackjokers += n - 3 - w; // Number of moves needed to neutralize Black's joker
					}
					nrmoves += b - w - 1; // Number of moves in this column
				}
			}

			// Determine the winner
			if ((n == 4 && doublejokers % 2 == 1) || whitejokers > blackjokers || (whitejokers >= blackjokers - 1 && nrmoves % 2 == 1)) 
				System.out.print("White wins\n");
			else System.out.print("Black wins\n");
		}
	}

}