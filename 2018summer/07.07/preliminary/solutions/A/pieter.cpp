// Solution to Choosing ice cream
// Author: Pieter Bootsma

// @EXPECTED_RESULTS@: CORRECT

#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

map<int, int> factor(int n)
{
	map<int, int> r;
	for (int i = 2; i <= (int)sqrt(n); i++)
	{
		while ((n % i) == 0)
		{
			n /= i;
			r[i]++;
		}
	}
	if (n > 1)
	{
		r[n]++;
	}
	return r;
}

struct CompareFactors
{
	bool operator()(const pair<const int, int> &a, const pair<const int, int> &b) const
	{
		return a.first < b.first;
	}
};

void dostep()
{
	int n, k;
	cin >> n >> k;
	
	// Two special cases
	if (n == 1)
	{
		cout << 0 << endl;
	}
	else if (k == 1)
	{
		cout << "unbounded" << endl;
	}
	else
	{
		// Determine prime factors in n and k
		map<int, int> n_factors = factor(n);
		map<int, int> k_factors = factor(k);
		
		// Determine prime factors in n not in k, and vice versa
		map<int, int> n_extra;
		map<int, int> k_extra;
		
		set_difference(n_factors.begin(), n_factors.end(), k_factors.begin(), k_factors.end(), inserter(n_extra, n_extra.begin()), CompareFactors());
		set_difference(k_factors.begin(), k_factors.end(), n_factors.begin(), n_factors.end(), inserter(k_extra, k_extra.begin()), CompareFactors());
		
		// If n has prime factors not in k, it is impossible
		if (!n_extra.empty())
		{
			cout << "unbounded" << endl;
		}
		else
		{
			// Remove all extra prime factors from k
			for (auto it : k_extra)
			{
				k /= it.first * it.second;
				k_factors.erase(it.first);
			}
			
			if (n > k)
			{
				// For every factor that occurs more often in n than in k, we need extra throws
				int throws = 1;
				
				for (auto it : n_factors)
				{
					int i = it.first;
					
					int nf = n_factors[i];
					int kf = k_factors[i];
					
					// f = ceil(nf / kf)
					int f = (nf + kf - 1) / kf;
					
					// The number of extra throws we need is the maximum of the extra throws
					// we need for every independent prime factor
					throws = max(throws, f);
				}
				
				cout << throws << endl;
			}
			else if ((k % n) == 0)
			{
				// k is multiple of n; always in 1 throw
				cout << 1 << endl;
			}
			else
			{
				// k is larger than n, but no exact multiple; not possible
				cout << "unbounded" << endl;
			}
		}
	}
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
