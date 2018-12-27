// Solution to Key to Knowledge
// Author: Thomas Beuman

// Time complexity: O(n!/(n/2)!^2) (worst case)
// Memory: O(n*m)

// @EXPECTED_RESULTS@: TIMELIMIT

// Solution method: Brute force with pruning

#include <cstdio>
#include <cstring>
using namespace std;

const int nmax = 12, mmax = 30;

bool StudentAnswer[nmax][mmax];
int StudentScore[nmax][mmax+1];
// StudentScore[i][j] = number of correct answers of student i among the first j questions

bool Answer[mmax], Solution[mmax];
int Bin[mmax+1][mmax+1]; // Binomial coefficient

int n;

int nrofsolutions (int q)
{	if (q == 0) // No questions left
	{	memcpy(Solution, Answer, sizeof(Solution));
		return 1;
	}
	int i, nsol = 0, ans;
	// Try both true and false as answer to question q-1
	for (ans = 0; ans < 2; ans++)
	{	// Update all scores
		for (i = 0; i < n; i++)
		{	StudentScore[i][q-1] = StudentScore[i][q] - (StudentAnswer[i][q-1] ^ !ans);
			if (StudentScore[i][q-1] < 0 || StudentScore[i][q-1] >= q) // Check if within bounds
				break;
		}
		if (i == n) // No one's score is out of bounds
		{	Answer[q-1] = ans;
			nsol += nrofsolutions(q-1); // Recursively proceed with remaining questions
		}
	}
	return nsol;
}

int bin (int n, int k)
{	return n >= 0 && k >= 0 && k <= n ? Bin[n][k] : 0;
}

int main()
{	int runs, run, m, d, i, j, k, s, s1, s2, nsol;
	char c;
	for (m = 0; m <= mmax; m++)
	{	Bin[m][0] = Bin[m][m] = 1;
		for (i = 1; i < m; i++)
			Bin[m][i] = Bin[m-1][i-1] + Bin[m-1][i];
	}
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d ", &n, &m);
		for (i = 0; i < n; i++)
		{	for (j = 0; j < m; j++)
			{	scanf("%c", &c);
				StudentAnswer[i][j] = (c == '1');
			}
			scanf("%d ", &StudentScore[i][m]);
		}

		/*** Some shortcuts ***/
		// Check if someone has all correct or all wrong
		for (i = 0; i < n && StudentScore[i][m] > 0 && StudentScore[i][m] < m; i++);
		if (i < n) // If so...
		{	s = StudentScore[i][m];
			for (j = 0; j < m; j++)
				Solution[j] = (s == 0) ^ StudentAnswer[i][j];
			// Check scores of all students
			for (i = 0; i < n; i++)
			{	s = 0;
				for (j = 0; j < m; j++)
					if (StudentAnswer[i][j] == Solution[j])
						s++;
				if (StudentScore[i][m] != s)
					break;
			}
			if (i < n)
				printf("0 solutions\n");
			else
			{	for (j = 0; j < m; j++)
					printf("%d", Solution[j]);
				printf("\n");
			}
			continue;
		}
		// Check that score + #trues has the same parity for all students
		for (i = 0; i < n; i++)
		{	s = StudentScore[i][m];
			for (j = 0; j < m; j++)
				if (StudentAnswer[i][j])
					s++;
			if (i == 0)
				k = s%2;
			else if ((s+k)%2 == 1)
				break;
		}
		if (i < n)
		{	printf("0 solutions\n");
			continue;
		}
		// Single student
		if (n == 1)
		{	printf("%d solutions\n", Bin[m][StudentScore[0][m]]);
			continue;
		}
		// Two students
		if (n == 2)
		{	d = 0;
			s1 = StudentScore[0][m];
			s2 = StudentScore[1][m];
			// Count questions where they disagree
			for (j = 0; j < m; j++)
				if (StudentAnswer[0][j] != StudentAnswer[1][j])
					d++;
			k = (d+s1-s2)/2; // Number of correct answers of student 1 among these questions
			nsol = bin(d, k) * bin(m-d, s1-k);
			printf("%d solutions\n", nsol);
			continue;
		}

		nsol = nrofsolutions(m);
		// Print answer
		if (nsol == 1)
		{	for (j = 0; j < m; j++)
				printf("%d", Solution[j]);
			printf("\n");
		}
		else
			printf("%d solutions\n", nsol);
	}
	return 0;
}
