// Solution to Word Search
// Author: Thomas Beuman

// Time complexity: O(n*h*w*wordlength)
// Memory: O(h*w)

// @EXPECTED_RESULTS@: CORRECT

#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int hmax = 32, wmax = 32, lmax = 32;

char Grid[hmax][wmax+1];
char Word[lmax+1];

bool Marked[hmax][wmax];
int di[] = {-1,-1,-1,0,0,1,1,1};
int dj[] = {-1,0,1,-1,1,-1,0,1};

int main()
{	int runs, run, n, h, w, d, i, j, k, m, s, i2, j2, solutions;
	bool nosolution, ambiguous, palindrome, empty;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{	
		// Read input
		scanf("%d %d %d", &n, &h, &w);
		for (i = 0; i < h; i++)
			scanf("%s", Grid[i]);

		memset(Marked, false, sizeof(Marked));
		nosolution = ambiguous = false;

		// Process the words
		for (s = 0; s < n; s++)
		{	scanf("%s", Word);
			m = strlen(Word);
			// Check if palindrome
			for (k = 0; k < (m-1)/2 && Word[k] == Word[m-1-k]; k++);
			palindrome = (k == (m-1)/2);
			solutions = 0;

			// Try all starting positions and directions
			for (i = 0; i < h; i++)
				for (j = 0; j < w; j++)
					for (d = 0; d < 8; d++)
					{	for (k = 0; k < m; k++)
						{	i2 = i + k * di[d];
							j2 = j + k * dj[d];
							if (i2 < 0 || i2 >= h || j2 < 0 || j2 >= w || Grid[i2][j2] != Word[k])
								break;
						}
						if (k == m) // Word found
						{	for (k = 0; k < m; k++)
								Marked[i+k*di[d]][j+k*dj[d]] = true;
							solutions++;
						}
					}
			if (solutions == 0)
				nosolution = true;
			if (!(solutions == 1 || (palindrome && solutions == 2) || (m == 1 && solutions == 8)))
				ambiguous = true;
		}

		// Print answer
		if (nosolution)
			printf("no solution\n");
		else if (ambiguous)
			printf("ambiguous\n");
		else
		{	// Print unmarked letters
			empty = true;
			for (i = 0; i < h; i++)
				for (j = 0; j < w; j++)
					if (!Marked[i][j])
					{	printf("%c", Grid[i][j]);
						empty = false;
					}
			if (empty)
				printf("empty solution");
			printf("\n");
		}
	}
	return 0;
}
