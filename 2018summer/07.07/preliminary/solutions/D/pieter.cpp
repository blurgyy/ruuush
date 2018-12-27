// Solution to Elevator problems
// Author: Pieter Bootsma

// Time complexity: O(n^2)
// Memory: O(n^2)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: DP

#include <climits>
#include <iostream>

using namespace std;

const int MAX_FLOORS = 1505;

int n;
int s[MAX_FLOORS];
int D[MAX_FLOORS][MAX_FLOORS];

void dostep()
{
	// Read input
	cin >> n;
	
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
	}
	
	// D[F][L] = least anger at/after floor F with last stop at floor L
	// D[0][0] = 0 -- nobody gets angry just by getting in the elevator; this program is fast!
	// D[F][L < F] = D[F-1][L] + (sum_{i=L+1}^{F} s_i)
	//     -- If the elevator does not stop at floor F, everyone who has to get out since the
	//        last stop is annoyed some more. Note that this can be calculated in O(n) instead of
	//        O(n^2) time for all L < F by looping L from F-1 to 0 and keeping the the running
	//        sum over s_i in s_sum.
	// D[F][F] = (min_{l=0}^{F-1} D[F-1][l]) + (sum_{i=F+1}^{n} s_i)
	//     -- If the elevator does stop at floor F, find the last floor where the elevator stopped
	//        that minimized anger, and add anger for everyone who does not yet have to get out.
	
	D[0][0] = 0;
	for (int F = 1; F <= n; F++)
	{
		int s_sum = 0;
		for (int L = F-1; L >= 0; L--)
		{
			s_sum += s[L+1];
			D[F][L] = D[F-1][L] + s_sum;
		}
		
		// Special case L = F
		D[F][F] = INT_MAX; // base case for min(): min(INT_MAX, x) == x
		for (int l = 0; l < F; l++)
		{
			D[F][F] = min(D[F][F], D[F-1][l]);
		}
		for (int i = F+1; i <= n; i++)
		{
			D[F][F] += s[i];
		}
	}
	
	// Always assume a stop at the top; this is never worse than not stopping there
	cout << D[n][n] << endl;
}

int main(int, char**)
{
	int n;
	cin >> n;
	while (n--)
	{
		dostep();
	}
	
	return 0;
}
