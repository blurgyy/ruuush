// Solution to Choosing Ice Cream
// Author: Thomas Beuman

// Time complexity: O(log(n))
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: modular exponentiation

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{	int runs, run, n, k, t;
	long long p;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{	// Read input
		scanf("%d %d", &n, &k);

		// Find smallest t such that p = k**t = 0 (mod n)
		for (t = 0, p = 1%n; t < 30 && p != 0; t++, p = (k*p) % n);
		if (t == 30)
			printf("unbounded\n");
		else
			printf("%d\n", t);
	}
	return 0;
}
