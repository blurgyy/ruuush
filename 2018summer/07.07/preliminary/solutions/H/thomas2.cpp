// Solution to Talent Selection
// Author: Thomas Beuman

// Time complexity: O(n*log(n))
// Memory: O(nmax+dmax)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: Binary search

#include <algorithm>
#include <cstdio>
using namespace std;

const int nmax = 1000000;

int T[nmax], P[nmax];

int main()
{	int runs, run, n, s, f, k, i, t, lowerbound, upperbound, threshold;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %d", &n, &s, &f);
		for (i = 0; i < n; i++)
			scanf("%d", &T[i]);
		scanf("%d", &k);
		for (i = 0; i < k; i++)
			scanf("%d", &P[i]);

		sort(T, T+f); // Sort favourites by points
		sort(T+f, T+n); // Sort others by points
		lowerbound = max(0, s-(n-f)); // Number of favourites you certainly can get selected
		upperbound = min(f,s)+1; // Number of favourites you certainly cannot get selected

		// Binary search
		while (lowerbound < upperbound-1)
		{	t = (lowerbound+upperbound)/2; // Target
			threshold = T[n-1-(s-t)]; // Non-favourite to beat
			// Distribute points remaining after rewarding f favourites and s-t non-favourites
			for (i = 0; i < k-f-(s-t); i++)
				threshold = max(threshold, T[k-1-s+t-i] + P[i]);
			// Check if the top t favourites can beat the threshold
			for (i = 0; i < t && T[f-1-i] + (k-t+i < 0 ? 0 : P[k-t+i]) >= threshold; i++);
			if (i == t)
				lowerbound = t;
			else
				upperbound = t;
		}

		// Print answer
		printf("%d\n", lowerbound);
	}
	return 0;
}
