// Solution to Lift Problems
// Author: Thomas Beuman

// Time complexity: O(n^2)
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: Dynamic programming

#include <algorithm>
#include <cstdio>
using namespace std;

const int nmax = 1500;

const int infty = 1<<30;

int S[nmax+1];
int Anger[nmax+1]; // Anger[i] = minimum total anger when lift stops at floor i

int main()
{	int runs, run, n, i, j, skipanger, students;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d", &n);
		for (i = 1; i <= n; i++)
			scanf("%d", &S[i]);

		// Count total number of students
		students = 0;
		for (i = 1; i <= n; i++)
			students += S[i];

		// Dynamic programming
		Anger[0] = 0;
		for (i = 1; i <= n; i++)
		{	students -= S[i]; // Number of students that want to go higher
			skipanger = 0;
			Anger[i] = infty;
			// Try all possible previous stops
			for (j = i-1; j >= 0; j--)
			{	Anger[i] = min(Anger[i], Anger[j] + skipanger + students);
				skipanger += (i-j)*S[j];
			}
		}

		// Print answer
		printf("%d\n", Anger[n]);
	}
	return 0;
}
