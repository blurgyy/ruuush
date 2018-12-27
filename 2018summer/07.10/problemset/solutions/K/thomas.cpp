// Solution to Key to Knowledge
// Author: Thomas Beuman

// Time complexity: O(n*2^(n/2))
// Memory: O(2^(n/2))

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * Split the questions into two (roughly) equal sets.
 * For both sets, consider all possible combinations of answers.
 * For every combination, determine the (partial) score of each student.
 * Put all scores in a single 64-bit integer, with the first 5 bits
 *   representing the score of student 1, the next five that of student 2, etcetera.
 * This gives two lists of numbers, one for each set. The problem is now to find two numbers,
 *   one from each list, that add up to a certain number (representing everyone's total score).
 * Sort both lists. Consider the smallest number of one list and the largest of the other.
 * If their sum is too small, consider the next smallest number of the one list;
 *   if it is too large, take the next largest number of the other list.
 * Go through the lists and count the solutions.
 */

#include <algorithm>
#include <cstdio>
using namespace std;

const int nmax = 12, mmax = 30;

int StudentAnswers[nmax], StudentScore[nmax];

pair<long long,int> Scores1[1<<(mmax/2)], Scores2[1<<(mmax-mmax/2)]; // (scores, answers)

int score (int m, int solution, int answers)
{	return m - __builtin_popcount(solution ^ answers);
}

int main()
{	int runs, run, n, m, a, a1, a2, i, j, k1, k2, m1, m2, nsol, solution;
	long long s, s1, s2, target;
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

		// Accumulate all scores
		target = 0;
		for (i = 0; i < n; i++)
			target |= (((long long)StudentScore[i]) << (5*i));
		// Split questions in two parts
		m1 = m/2;
		m2 = m-m1;
		// Consider all possible answers to the first m1 questions
		for (a1 = 0; a1 < (1<<m1); a1++)
		{	// Accumulate scores
			s1 = 0;
			for (i = 0; i < n; i++)
				s1 |= ((long long)(score(m1, a1, StudentAnswers[i] >> m2))) << (5*i);
			Scores1[a1] = make_pair(s1, a1);
		}
		// Consider all possible answers to the last m2 questions
		for (a2 = 0; a2 < (1<<m2); a2++)
		{	// Accumulate scores
			s2 = 0;
			for (i = 0; i < n; i++)
				s2 |= ((long long)(score(m2, a2, StudentAnswers[i] & ((1<<m2)-1)))) << (5*i);
			Scores2[a2] = make_pair(s2, a2);
		}
		sort(Scores1, Scores1+(1<<m1));
		sort(Scores2, Scores2+(1<<m2));

		nsol = solution = 0;
		i = 0;
		j = (1<<m2)-1;
		while (i < (1<<m1) && j >= 0)
		{	s = Scores1[i].first + Scores2[j].first; // Overall score
			if (s == target) // Solution found
			{	solution = ((Scores1[i].second << m2) | Scores2[j].second);
				// Check for redundancy
				k1 = k2 = 1;
				for (i++; i < (1<<m1) && Scores1[i].first == Scores1[i-1].first; i++, k1++);
				for (j--; j >= 0 && Scores2[j].first == Scores2[j+1].first; j--, k2++);
				nsol += k1*k2;
			}
			else if (s < target) // Score too small: try next smallest Scores1
				i++;
			else // Score too large: try next largest Scores2
				j--;
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
