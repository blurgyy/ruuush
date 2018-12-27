// Solution to Icecream
// Author: Alex ten Brink

// Time complexity: O(log^2(n))
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: trying all options

#include "math.h"
#include <algorithm>
#include <iostream>
using namespace std;

long powermod(long k, long i, long n)
{
	long long acc = 1 % n;
	for (int j = 0; j < i; j++)
	{
		acc =  (acc *k) % n;
	}
	return acc;
}

int main()
{
	int runs;
	cin >> runs;
	while (runs > 0)
	{
		long n, k; bool found = false;
		cin >> n >> k;
		
		int i = 0;
		for (long j = 1; j <= n; j *= 2)
		{
			if (powermod(k, i, n) == 0)
			{
				cout << i << endl;
				found = true;
				break;
			}
			i++;
		}
		if (!found) cout << "unbounded" << endl;

		runs--;
	}
	
	return 0;
}
