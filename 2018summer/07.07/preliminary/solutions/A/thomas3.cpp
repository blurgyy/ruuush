// Solution to Choosing Ice Cream
// Author: Thomas Beuman

// Inspired by a solution submitted by Rudy van Vliet (Leiden)

// Time complexity: O(log(n))
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * Insight: n divides k^t iff n divides d^t, where d = gcd(n,k).
 * Hence n divides k^t iff n/d divides d^(t-1).
 * Let n' = n/d, k' = d and t' = t-1. Then n divides k^t iff n' divides k'^t'.
 * We can repeat this process.
 * If at some point we have n' = 1, then t' = 0 is the smallest t';
 *   t is then the number of iterations.
 * If it is not unbounded, we should eventually get t' = 0. Then n' = 1 must hold.
 * Hence, if we never reach n' = 1, it is unbounded.
 * We never reach n' = 1 iff at some point k' = 1 (and n' > 1).
 */

#include <algorithm>
#include <cstdio>
using namespace std;

// Greatest common divisor
int gcd (int a, int b)
{ return b ? gcd(b, a%b) : a;
}

int main()
{	int runs, run, n, k, t;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{	scanf("%d %d", &n, &k);
		for (t = 0; n > 1 && k > 1; t++)
		{ k = gcd(n, k);
		  n /= k;
		}
		if (n > 1)
			printf("unbounded\n");
		else
			printf("%d\n", t);
	}
	return 0;
}
