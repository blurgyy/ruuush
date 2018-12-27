// Solution to Word Search
// Author: Thomas Beuman

// Time complexity: O(n*h*w)
// Memory: O(h*w)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: Knuth-Morris-Pratt (KMP)

#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int hmax = 32, wmax = 32, lmax = 32;

char Grid[hmax][wmax+1];
char Word[lmax+1];

bool Marked[hmax][wmax];
int F[lmax+1];
int h, w, wordlength;

// Preprocess word
void kmp_init()
{	int i, j;
	F[0] = F[1] = 0;
	for (i = 2; i <= wordlength; i++)
		for (j = F[i-1]; true; j = F[j])
		{	if (Word[j] == Word[i-1])
			{	F[i] = j+1;
				break;
			}
			if (!j)
			{	F[i] = 0;
				break;
			}
		}
}

// Check the line starting from (i,j) in the direction (di,dj)
int kmp (int i, int j, int di, int dj)
{	int solutions = 0, linelength, k = 0, x = 0, y;
	// Determine line length
	linelength = min(di==-1 ? i+1 : di==1 ? h-i : w, dj==-1 ? j+1 : dj==1 ? w-j : h);
	while (wordlength-k <= linelength-x)
	{	if (Grid[i+x*di][j+x*dj] == Word[k])
		{	x++;
			k++;
			if (k == wordlength) // Solution found
			{	solutions++;
				for (y = x-k; y < x; y++)
					Marked[i+y*di][j+y*dj] = true;
				k = F[k];
			}
		}
		else if (k > 0)
			k = F[k];
		else
			x++;
	}
	return solutions;
}

int main()
{	int runs, run, n, i, j, k, s, solutions;
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
			if (nosolution)
				continue;
			wordlength = strlen(Word);
			// Check if palindrome
			for (k = 0; k < (wordlength-1)/2 && Word[k] == Word[wordlength-1-k]; k++);
			palindrome = (k == (wordlength-1)/2);

			solutions = 0;
			kmp_init();
			// Try all starting positions and directions
			for (j = 0; j < w; j++)
			{	// Top row
				solutions += kmp(0,j, 1,-1);
				solutions += kmp(0,j, 1,0);
				solutions += kmp(0,j, 1,1);
				// Bottom row
				solutions += kmp(h-1,j, -1,-1);
				solutions += kmp(h-1,j, -1,0);
				solutions += kmp(h-1,j, -1,1);
			}
			// Left and right columns
			for (i = 0; i < h; i++)
			{	solutions += kmp(i,0, 0,1);
				solutions += kmp(i,w-1, 0,-1);
				if (i > 0 && i < h-1) // Avoid processing corners again
				{	solutions += kmp(i,0, -1,1);
					solutions += kmp(i,0, 1,1);
					solutions += kmp(i,w-1, -1,-1);
					solutions += kmp(i,w-1, 1,-1);
				}
			}
			if (solutions == 0)
				nosolution = true;
			if (!(solutions == 1 || (palindrome && solutions == 2) || (wordlength == 1 && solutions == 8)))
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
