// Solution to Floating Formation
// Author: Thomas Beuman

// Time complexity: O(k*(m+n))
// Memory: O(n+m)

// @EXPECTED_RESULTS@: TIMELIMIT

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

const int nmax = 10000;

set<int> Adj[nmax], Conn[nmax];

int Leaf[nmax], MaxBranch[nmax];
bool InDanger[nmax];
bool Saved[nmax];

// "Sink" boat i if it has only one connection left, and recursively check its neighbour 
// Keep track of the length of the (longest) branch
void sink (int i, int brlen, int leaf)
{	if (brlen > MaxBranch[i])
	{	MaxBranch[i] = brlen; // The longest branch (so far) stemming from node i
		Leaf[i] = leaf;
	}
	if (Conn[i].size() == 1) // If the design will sink...
	{	InDanger[i] = true;
		int j = *(Conn[i].begin()); // Neighbouring design
		Conn[j].erase(i); // Remove boat
		sink(j, MaxBranch[i]+1, Leaf[i]); // Check neighbour
	}
}

int main()
{	int runs, run, n, m, k, a, b, i, j, willsink, tosave, maxbr;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %d", &n, &m, &k);
		for (i = 0; i < n; i++)
			Adj[i].clear();
		for (j = 0; j < m; j++)
		{	scanf("%d %d", &a, &b);
			Adj[a-1].insert(b-1);
			Adj[b-1].insert(a-1);
		}

		memset(Saved, false, sizeof(Saved));
		for (willsink = 1; k >= 0 && willsink > 0; k--)
		{	// Restore all connections
			for (i = 0; i < n; i++)
				Conn[i] = set<int>(Adj[i]);
			memset(InDanger, false, sizeof(InDanger));
			memset(MaxBranch, 0, sizeof(MaxBranch));
			// Find designs with only one boat and recursively see which ones they take down with them
			for (i = 0; i < n; i++)
				if (Conn[i].size() == 1 && MaxBranch[i] == 0 && !Saved[i])
					sink(i, 1, i);
			// Save the boat at the end of the largest branch
			willsink = tosave = maxbr = 0;
			for (i = 0; i < n; i++)
				if (InDanger[i])
				{	willsink++;
					if (MaxBranch[i] > maxbr)
					{	maxbr = MaxBranch[i];
						tosave = Leaf[i];
					}
				}
			Saved[tosave] = true;
		}
		printf("%d\n", willsink);
	}
	return 0;
}
