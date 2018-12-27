// Solution to Spy Network
// Author: Alex ten Brink

// Time complexity: O(n * \log^2(number size))
// Memory: O(n+m)

// @EXPECTED_RESULTS@: CORRECT

#include <stack>
#include <vector>
#include <iostream>
#include "math.h"
using namespace std;

long long gcd(long long a, long long b)
{
	while (b != 0)
	{
		long long t = b; b = a % b; a = t;
	}
	return a;
}

int n, m;
long long l;
long long *current;
vector<int> *edges;
int main()
{
	int runs;
	cin >> runs;
	while (runs > 0)
	{
		cin >> n >> m >> l;
		current = new long long[n];
		edges = new vector<int>[n];
		for (int k = 0; k < n; k++)
		{
			edges[k].clear();
		}
		for (int k = 0; k < m; k++)
		{
			int a, b;
			cin >> a >> b;
			edges[a-1].push_back(b-1);
		}
		for (int k = 0; k < n; k++)
		{
			cin >> current[k];
		}

		// Immediate smart propagation
		//int propagationCount = 0;
		bool* changed = new bool[n];
		for (int k = 0; k < n; k++) changed[k] = true;
		stack<int> S;
		for (int k = 0; k < n; k++) S.push(k);

		while (!S.empty())
		{
			int x = S.top(); S.pop();
			//cout << "treating " << x << endl;
			changed[x] = false;
			for (auto it = edges[x].begin(); it != edges[x].end(); ++it)
			{
				int y = *it;
				long long ycurrent = current[y];
				current[y] = gcd(current[x], current[y]);
				if (current[y] != ycurrent && !changed[y])
				{
					S.push(y);
					changed[y] = true;
					//propagationCount++;
					//cout << "updated " << y << " to " << current[y] << endl;
				}
			}
		}
		//cout << propagationCount << endl;
		delete[] changed;
		// /Immediate smart propagation

		int count = 0;
		for (int k = 0; k < n; k++)
		{
			if (current[k] == l) count++;
		}
		cout << count << endl;
		delete[] current;
		delete[] edges;
		runs--;
	}
	return 0;
}
