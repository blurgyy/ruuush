// Solution to Interesting Integers
// Author: Thomas Beuman

// Time complexity: O(log(n))
// Memory: O(log(n))

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * n  =  G(k)  =  a F(k-2) + b F(k-1)  =  (b-a) F(k-1) + a F(k)  =  c F(k-1) + a F(k)  [c >= 0]
 * Goal: maximize k and minimize c
 * Try all k in decreasing order
 * n  =  c F(k-1) [mod F(k)]   =>   c  =  n F(k-1)^(-1) [mod F(k)]  =  n F(k-1-k%2) [mod F(k)]
 * Minimize c:  c  =  n F(k-1-k%2) % F(k)
 * If  c F(k-1) < n  then:
 *   a = (n - c F(k-1)) / F(k)
 *   b = a+c
 */

#include <cstdio>
using namespace std;

const int nmax = 1000000000;

long long F[99];

int main()
{	int runs, run, n, a, b, c, k, m;

	// Calculate Fibonacci numbers
	F[1] = F[2] = 1;
	for (m = 3; (F[m] = F[m-1] + F[m-2]) <= nmax; m++);

	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		scanf("%d", &n);

		// Try all k in decreasing order
		for (k = m-1; k > 2; k--)
		{	c = (n * F[k-1-k%2]) % F[k]; // Determine c = b-a
			if (c*F[k-1] < n) // Check if this gives a solution
				break;
		}

		// Find a and b and print
		a = (n-c*F[k-1]) / F[k];
		b = a+c;
		printf("%d %d\n", a, b);
	}
	return 0;
}
