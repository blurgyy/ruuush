// Solution to Citadel Construction
// Author: Thomas Beuman

// Time complexity: O(n^2)
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * Insight: the vertices that make up the optimal solution lie on the convex hull.
 * Find the convex hull and index the points in counterclockwise order.
 * Let abcd describe the quadrangle, with a having the lowest index.
 * Loop over all a. For each a, initialize b to a and d to a+1, loop over all c starting from a+1.
 * For each c, increase b and d until they are optimal with respect to a and c.
 * Find the maximum over all a and c.
 */

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
{	int runs, run, n, a, b, c, d, i, m, amax;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d %d", &X[i], &Y[i]);
		m = convexhull(n);
		amax = 0;
		for (a = 0; a < m; a++)
		{	b = a;
			d = a+1;
			for (c = a+1; c < m; c++)
			{	while (b < c && area2(a,b,c) <= area2(a,b+1,c))
					b++;
				while (d < m-1 && area2(c,d,a) <= area2(c,d+1,a))
					d++;
				amax = max(amax, area2(a,b,c) + area2(c,d,a));
			}
		}
		if (amax % 2 == 0)
			printf("%d\n", amax/2);
		else
			printf("%d.5\n", amax/2);
	}
	return 0;
}
