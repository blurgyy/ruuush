// Solution to Pawns
// Author: Thomas Beuman

// Time complexity: O(n*m)
// Memory: O(n*m)

// @EXPECTED_RESULTS@: CORRECT

#include <cstdio>
#include <cstring>
using namespace std;

const int nmax = 20, mmax = 20;

char Board[nmax][mmax+1];

int main()
{	int runs, run, n, m, i, j, b, w, nrmoves, whitejokers, blackjokers, doublejokers;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{	
		// Read input
		scanf("%d %d", &n, &m);
		for (i = 0; i < n; i++)
			scanf("%s", Board[n-1-i]);
		nrmoves = whitejokers = blackjokers = doublejokers = 0;

		// Traverse the columns
		for (j = 0; j < m; j++)
		{	
			// Find pawns
			for (i = 0; Board[i][j] != 'W'; i++);
			w = i;
			for (i++; Board[i][j] != 'B'; i++);
			b = i;

			if (w == 0 && b == n-1 && n > 3) // Both pawns on their first rank (n>3)
				doublejokers++;
			else
			{	if (w == 0 && b > 2)
					whitejokers += b-2; // Number of moves needed to neutralize White's joker
				else if (b == n-1 && w < n-3)
					blackjokers += n-3-w; // Number of moves needed to neutralize Black's joker
				nrmoves += b-w-1; // Number of moves in this column
			}
		}

		// Determine the winner
		printf("%s wins\n", (n == 4 && doublejokers % 2 == 1) ||
		                    whitejokers > blackjokers ||
		                    (whitejokers >= blackjokers - 1 && nrmoves % 2 == 1) ? "White" : "Black");
	}
	return 0;
}
