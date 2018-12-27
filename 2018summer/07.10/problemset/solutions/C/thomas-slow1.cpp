// Solution to Citadel Construction
// Author: Thomas Beuman

// Time complexity: O(n^3)
// Memory: O(n)

// @EXPECTED_RESULTS@: TIMELIMIT

// Solution method: Brute force over all triangles

#include <algorithm>
#include <cstdio>
using namespace std;

const int nmax = 1000;

int X[nmax], Y[nmax];

// Returns the area of a triangle (times two)
// The answer is negative iff the loop a->b->c->a is clockwise
int area2 (int a, int b, int c)
{	return X[a]*Y[b] - X[b]*Y[a] + X[b]*Y[c] - X[c]*Y[b] + X[c]*Y[a] - X[a]*Y[c];
}

int main()
{	int runs, run, n, a, i, j, k, amax, aminij, amaxij;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d %d", &X[i], &Y[i]);
		amax = 0;
		for (i = 0; i < n; i++)
			for (j = 0; j < i; j++)
			{	aminij = amaxij = 0;
				for (k = 0; k < i; k++)
				{	a = area2(i, j, k);
					aminij = min(aminij, a);
					amaxij = max(amaxij, a);
				}
				amax = max(amax, amaxij - aminij);
			}
		if (amax % 2 == 0)
			printf("%d\n", amax/2);
		else
			printf("%d.5\n", amax/2);
	}
	return 0;
}
