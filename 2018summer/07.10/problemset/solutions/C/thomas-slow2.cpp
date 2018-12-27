// Solution to Citadel Construction
// Author: Thomas Beuman

// Time complexity: O(n*m+m^3) (m = #vertices on convex hull, max n)
// Memory: O(n)

// @EXPECTED_RESULTS@: TIMELIMIT

// Solution method: Brute force over all triangles (among the vertices on the convex hull)

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

// Gift wrap algorithm (O(n*m))
// Returns number of vertices m
int convexhull (int n)
{	int m, i, j = 0;
	// Find leftmost vertex
	for (i = 1; i < n; i++)
		if (X[i] < X[j])
			j = i;
	// Put at the front
	swap(X[0], X[j]);
	swap(Y[0], Y[j]);
	for (m = 1; true; m++)
	{	// Find the vertex that is furthest to the right w.r.t. vertex m-1
		j = (m==1?1:0); // Start with 0, unless vertex m-1 is 0
		for (i = 0; i < n; i++)
			if (area2(m-1, i, j) > 0) // If (m-1)->i->j->(m-1) is counterclockwise
				j = i;
		if (j == 0) // Back to start
			return m;
		swap(X[m], X[j]);
		swap(Y[m], Y[j]);
	}
}

int main()
{	int runs, run, n, a, i, j, k, m, amax, aminij, amaxij;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d %d", &X[i], &Y[i]);
		m = convexhull(n);
		amax = 0;
		for (i = 0; i < m; i++)
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
