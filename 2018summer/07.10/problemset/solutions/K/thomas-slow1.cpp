// Solution to Key to Knowledge
// Author: Thomas Beuman

// Time complexity: O(2^n)
// Memory: O(n)

// @EXPECTED_RESULTS@: TIMELIMIT

// Solution method: Brute force

#include <cstdio>
using namespace std;

const int nmax = 12, mmax = 30;

const int none = -1, multiple = -2;

int StudentAnswers[nmax], StudentScore[nmax];

int score (int m, int solution, int answers)
{	return m - __builtin_popcount(solution ^ answers);
}

int main()
{	int runs, run, n, m, a, i, j, nsol, solution;
	char c;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d ", &n, &m);
		for (i = 0; i < n; i++)
		{	a = 0;
			for (j = 0; j < m; j++)
			{	scanf("%c", &c);
				a = 2*a + (c-'0');
			}
			StudentAnswers[i] = a;
			scanf("%d ", &StudentScore[i]);
		}

		nsol = solution = 0;
		// Try all combinations of answers
		for (a = (1<<m)-1; a >= 0; a--)
		{	// Check scores
			for (i = 0; i < n && score(m, a, StudentAnswers[i]) == StudentScore[i]; i++);
			if (i == n) // Solution found
			{	nsol++;
				solution = a;
			}
		}

		// Print answer
		if (nsol == 1)
		{	for (j = m-1; j >= 0; j--)
				printf("%d", !!(solution & (1<<j)));
			printf("\n");
		}
		else
			printf("%d solutions\n", nsol);
	}
	return 0;
}
