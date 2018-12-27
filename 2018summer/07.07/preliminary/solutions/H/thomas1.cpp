// Solution to Talent Selection
// Author: Thomas Beuman

// Time complexity: O(n*log(n)^2)
// Memory: O(nmax+dmax)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: Binary search

#include <algorithm>
#include <cstdio>
using namespace std;

const int nmax = 1000000;

struct candidate
{	int points;
	bool favourite;
	candidate() {}
	candidate (int p, bool f) : points(p), favourite(f) {}
};

bool operator < (candidate A, candidate B)
{	return A.points < B.points || (A.points == B.points && !A.favourite && B.favourite);
}

candidate operator + (candidate A, int p)
{	A.points += p;
	return A;
}

candidate Favs[nmax], Others[nmax], All[nmax];
int P[nmax];

int main()
{	int runs, run, n, s, f, k, a, i, j, t, lowerbound, upperbound;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %d", &n, &s, &f);
		for (i = 0; i < f; i++)
		{	scanf("%d", &t);
			Favs[i] = candidate(t, true);
		}
		for (i = 0; i < n-f; i++)
		{	scanf("%d", &t);
			Others[i] = candidate(t, false);
		}
		scanf("%d", &k);
		// Store points in decreasing order
		for (i = k-1; i >= 0; i--)
			scanf("%d", &P[i]);
		// Add zeros
		for (i = k; i < n; i++)
			P[i] = 0;

		sort(Favs, Favs+f); // Sort favourites by points
		sort(Others, Others+n-f); // Sort others by points
		lowerbound = max(0, s-(n-f)); // Number of favourites you certainly can get selected
		upperbound = min(f,s)+1; // Number of favourites you certainly cannot get selected

		// Binary search
		while (lowerbound < upperbound-1)
		{	t = (lowerbound+upperbound)/2; // Target
			j = 0;
			// Award points to top t favourites
			for (i = f-t; i < f; i++, j++)
				All[j] = Favs[i] + P[j];
			// Award points to other favourites
			for (i = 0; i < f-t; i++, j++)
				All[j] = Favs[i] + P[j];
			// Award points to s-t non-favourites (who may go through)
			for (i = n-f-(s-t); i < n-f; i++, j++)
				All[j] = Others[i] + P[j];
			// Award points to remaining non-favourites
			for (i = 0; i < n-f-(s-t); i++, j++)
				All[j] = Others[i] + P[j];
			sort(All, All+n); // Determine rankings
			// Count selected favourites
			a = 0;
			for (i = 0; i < s; i++)
				if (All[n-1-i].favourite)
					a++;
			// Update bounds
			if (a >= t)
				lowerbound = t;
			else
				upperbound = t;
		}

		// Print answer
		printf("%d\n", lowerbound);
	}
	return 0;
}
