// Solution to Icecream
// Author: Kevin Buchin

// Time complexity: O(log(n))
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: testing k^i/N \in \N, but using modulo excessively

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int runs;
	cin >> runs;

	while (runs--)
	{
		unsigned long n, k;
		unsigned long long r;
		
		cin >> n >> k;
		
		r = 1 % n;
		k = k % n;
		
		for (unsigned int i=0; i <= 32; i++)
		{
			if (r == 0) {
				cout << i << endl;
				break;
			}
			r = (r*k)%n;
		}
		if (r != 0) cout << "unbounded" << endl;
	}
	
	return 0;
}
