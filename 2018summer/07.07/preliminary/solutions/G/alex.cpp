// Solution to Spy network
// Author: Alex ten Brink

// Time complexity: O(n + m \log^2(number size))
// Memory: O(n+m)

// @EXPECTED_RESULTS@: CORRECT

#include <stack>
#include <vector>
#include <iostream>
#include "math.h"
using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
	while (b != 0)
	{
		long long t = b; b = a % b; a = t;
	}
	return a;
}

int n, m;
long long l;
long long *initial;
long long *current;
vector<int> *edges;
int index;
stack<int> S;
int *indices;

int dopop()
{
	int result = S.top();
	S.pop();
	return result;
}

void traverse(int x)
{
	S.push(x);
	int d = S.size();
	indices[x] = d; current[x] = initial[x]; //cout << x << ": " << current[x] << endl;
	for (auto it = edges[x].begin(); it != edges[x].end(); ++it)
	{
		int y = *it;
		if (indices[y] == 0) traverse(y);
		indices[x] = min(indices[x], indices[y]); current[x] = gcd(current[x], current[y]); //cout << x << ": " << current[x] << endl;
	}
	if (indices[x] == d)
	{
		do
		{
			indices[S.top()] = n; current[S.top()] = current[x]; //cout << S.top() << ": " << current[S.top()] << endl;
		}
		while (dopop() != x);
	}
}

int main()
{
	int runs;
	cin >> runs;
	while (runs > 0)
	{
		cin >> n >> m >> l;
		initial = new long long[n];
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
			edges[b-1].push_back(a-1); // reversed!
		}
		for (int k = 0; k < n; k++)
		{
			cin >> initial[k];
		}

		// Tarjan
		index = 0;
		indices = new int[n];
		while (!S.empty()) S.pop();

		for (int k = 0; k < n; k++) indices[k] = 0;
		for (int k = 0; k < n; k++)
		{
			if (indices[k] == 0)
				traverse(k);
		}

		delete[] indices;
		// /Tarjan

		int count = 0;
		for (int k = 0; k < n; k++)
		{
			if (current[k] == l) count++;
		}
		cout << count << endl;
		delete[] initial;
		delete[] current;
		delete[] edges;
		runs--;
	}
	return 0;
}
