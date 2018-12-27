// Solution to Key to Knowledge
// Author: Thomas Beuman

// Time complexity: O(n*m*2^(n/2))
// Memory: O(2^(n/2))

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * Split the questions into two (roughly) equal sets.
 * For both sets, consider all possible combinations of answers.
 * For every combination, determine the (partial) score of each student; put this in a vector.
 * This gives two lists of vectors, one for each set. The problem is now to find two vectors,
 *   one from each list, that add up to a certain vector (representing everyone's total score).
 * Sort both lists (lexicographically).
 * Consider the "smallest" vector of one list and the "largest" of the other.
 * If their sum is too small, consider the next smallest number of the one list;
 *   if it is too large, take the next largest number of the other list.
 * Go through the lists and count the solutions.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int nmax = 12, mmax = 30;

vector<bool> StudentAnswers1[nmax], StudentAnswers2[nmax];
vector<int> StudentScore;

pair<vector<int>,vector<bool> > Scores1[1<<(mmax/2)], Scores2[1<<(mmax-mmax/2)]; // (scores, answers)

int score (vector<bool>& solution, vector<bool>& answers)
{	int m = solution.size(), j, s = 0;
	for (j = 0; j < m; j++)
		if (solution[j] == answers[j])
			s++;
	return s;
}

vector<bool> concat (vector<bool> A, vector<bool>& B)
{	int m = B.size(), j;
	for (j = 0; j < m; j++)
		A.push_back(B[j]);
	return A;
}

vector<int> operator + (vector<int> A, vector<int>& B)
{	int n = A.size(), i;
	for (i = 0; i < n; i++)
		A[i] += B[i];
	return A;
}

bool operator < (vector<int>& A, vector<int>& B)
{	int n = A.size(), i;
	for (i = 0; i < n; i++)
		if (A[i] != B[i])
			return A[i] < B[i];
	return false;
}

bool operator == (vector<int>& A, vector<int>& B)
{	int n = A.size(), i;
	for (i = 0; i < n; i++)
		if (A[i] != B[i])
			return false;
	return true;
}

int main()
{	int runs, run, n, m, a1, a2, i, j, k1, k2, m1, m2, nsol;
	vector<bool> answers, solution;
	vector<int> s, s1, s2;
	char c;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d ", &n, &m);
		// Split questions in two parts
		m1 = m/2;
		m2 = m-m1;
		StudentScore.resize(n);
		for (i = 0; i < n; i++)
		{	StudentAnswers1[i].resize(m1);
			StudentAnswers2[i].resize(m2);
			for (j = 0; j < m; j++)
			{	scanf("%c", &c);
				if (j < m1)
					StudentAnswers1[i][j] = (c == '1');
				else
					StudentAnswers2[i][j-m1] = (c == '1');
			}
			scanf("%d ", &StudentScore[i]);
		}

		// Consider all possible answers to the first m1 questions
		answers.resize(m1);
		s1.resize(n);
		for (a1 = 0; a1 < (1<<m1); a1++)
		{	// Accumulate scores
			for (j = 0; j < m1; j++)
				answers[j] = !!(a1 & (1<<j));
			for (i = 0; i < n; i++)
				s1[i] = score(answers, StudentAnswers1[i]);
			Scores1[a1] = make_pair(s1, answers);
		}
		// Consider all possible answers to the last m2 questions
		answers.resize(m2);
		s2.resize(n);
		for (a2 = 0; a2 < (1<<m2); a2++)
		{	// Accumulate scores
			for (j = 0; j < m2; j++)
				answers[j] = !!(a2 & (1<<j));
			for (i = 0; i < n; i++)
				s2[i] = score(answers, StudentAnswers2[i]);
			Scores2[a2] = make_pair(s2, answers);
		}
		sort(Scores1, Scores1+(1<<m1));
		sort(Scores2, Scores2+(1<<m2));

		nsol = 0;
		i = 0;
		j = (1<<m2)-1;
		while (i < (1<<m1) && j >= 0)
		{	s = Scores1[i].first + Scores2[j].first; // Overall score
			if (s < StudentScore) // Score too small: try next smallest Scores1
				i++;
			else if (StudentScore < s) // Score too large: try next largest Scores2
				j--;
			else // Solution found
			{	solution = concat(Scores1[i].second, Scores2[j].second);
				// Check for redundancy
				k1 = k2 = 1;
				for (i++; i < (1<<m1) && Scores1[i].first == Scores1[i-1].first; i++, k1++);
				for (j--; j >= 0 && Scores2[j].first == Scores2[j+1].first; j--, k2++);
				nsol += k1*k2;
			}
		}
		
		// Print answer
		if (nsol == 1)
		{	for (j = 0; j < m; j++)
				printf("%d", solution[j]?1:0);
			printf("\n");
		}
		else
			printf("%d solutions\n", nsol);
	}
	return 0;
}
