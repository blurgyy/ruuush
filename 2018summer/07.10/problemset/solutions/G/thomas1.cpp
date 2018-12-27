// Solution to Growling Gears
// Author: Thomas Beuman

// Time complexity: O(n)
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

#include <cstdio>
using namespace std;

int main()
{	int runs, run, n, a, b, c, i, best;
	double T, Tmax;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{	scanf("%d", &n);
		best = 0;
		Tmax = 0;
		for (i = 1; i <= n; i++)
		{	scanf("%d %d %d", &a, &b, &c);
			T = b*b/(4.*a) + c;
			if (T > Tmax)
			{	Tmax = T;
				best = i;
			}
		}
		printf("%d\n", best);
	}
	return 0;
}
