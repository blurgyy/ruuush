// Solution to Excellent Engineers
// Author: Thomas Beuman

// Time complexity: O(n*log(n))
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * Sort the engineers by the first rank. Process the engineers from low rank to high rank
 *   (so that every new engineer is definitely not worse than those still to come).
 * Keep a set of all engineers, ordered by their second rank,
 *   for whom there is no other engineer (so far) with a lower second and third rank.
 * For every new engineer, find the person in the set with the next highest second rank
 *   (if anyone has the new engineer beat, it will be this person).
 * The new engineer goes on the shortlist iff he has a lower third rank than this person.
 * If on the shortlist, update the set by removing all persons
 *   with a higher second and third rank than the new engineer, and add him.
 */

#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;

const int nmax = 100000;

struct engineer
{	int r1, r2, r3;
	engineer() {}
	engineer(int s1, int s2, int s3) : r1(s1), r2(s2), r3(s3) {}
};

struct comparefirst
{	bool operator() (engineer A, engineer B)
	{	return A.r1 < B.r1;
	}
} cmp1;

struct comparesecond
{	bool operator() (engineer A, engineer B)
	{	return A.r2 < B.r2;
	}
};

engineer E[nmax];
set<engineer, comparesecond> S;

int main()
{	int runs, run, n, r1, r2, r3, c, i;
	set<engineer>::iterator it, itprev, itnext;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{	scanf("%d %d %d", &r1, &r2, &r3);
			E[i] = engineer(r1,r2,r3);
		}

		sort(E, E+n, cmp1); // Sort the engineers by their first rank
		// Put the first engineer on the shortlist and add him to the set
		c = 1;
		S.clear();
		S.insert(E[0]);
		// Process the other engineers
		for (i = 1; i < n; i++)
		{	itnext = S.lower_bound(E[i]); // Person with next lowest second rank
			itprev = itnext;
			itprev--; // Person with next highest second rank
			if (itnext == S.begin() || E[i].r3 < itprev->r3) // Compare third rank
			{	c++;
				// Remove engineers with higher second and third rank
				for (it = itnext; it != S.end() && E[i].r3 < it->r3;)
					S.erase(it++);
				S.insert(E[i]); // Add to set
			}
		}

		// Print answer
		printf("%d\n", c);
	}
	return 0;
}
