// Solution to Choosing Ice Cream
// Author: Thomas Beuman

// Time complexity: O(sqrt(n))
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method: prime factorization
 *
 * For all primefactors p of n, count the number of times it divides n (qn) and k (qk).
 * The answer is max(ceil(qn/qk)) over all p (unbounded if qk = 0).
 */

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{	int runs, run, n, k, i, qn, qk, t;
	bool unbounded;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{	// Read input
		scanf("%d %d", &n, &k);
		// Base case
		if (n == 1)
		{	printf("0\n");
			continue;
		}
		t = 1;
		unbounded = false;

		// Look for all primefactors of n
		for (i = 2; i*i <= n; i++)
		{	// Count number of divisions
			for (qn = 0; n % i == 0; n /= i, qn++);
			for (qk = 0; k % i == 0; k /= i, qk++);
			if (qn > 0)
			{	if (qk == 0)
				{	unbounded = true;
					break;
				}
				else
					t = max(t, 1+(qn-1)/qk); // qn/qk rounded up
			}
		}
		if (k % n > 0)
			unbounded = true;

		// Print answer
		if (unbounded)
			printf("unbounded\n");
		else
			printf("%d\n", t);
	}
	return 0;
}
