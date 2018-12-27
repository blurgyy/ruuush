// Solution to Floating Formation
// Author: Thomas Beuman

// Time complexity: O(m+n*log(n))
// Memory: O(n+m)

// @EXPECTED_RESULTS@: WRONG-ANSWER

// Does not compute the branch lengths correctly

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

const int nmax = 10000;

set<int> Adj[nmax];

int MaxBranch[nmax];
int Idx[nmax];
vector<int> Child[nmax];

bool cmp (int i, int j)
{	return MaxBranch[i] < MaxBranch[j];
}

// "Sink" boat i and recursively sink its neighbour if it has only one connection left
// Keep track of the length of the (longest) branch
void sink (int i, int brlen)
{	MaxBranch[i] = max(MaxBranch[i], brlen); // The longest branch (so far) stemming from node i
	int j = *(Adj[i].begin()); // Neighbouring design
	Child[j].push_back(i);
	Adj[j].erase(i); // Remove boat
	if (Adj[j].size() == 1) // If the design will sink...
		sink(j, MaxBranch[i]+1); // ...sink it!
}

int main()
{	int runs, run, n, m, k, a, b, i, j, q, willsink;
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

		for (i = 0; i < n; i++)
			Child[i].clear();
		memset(MaxBranch, 0, sizeof(MaxBranch));
		// Find designs with only one boat and recursively see which ones they take down with them
		for (i = 0; i < n; i++)
			if (Adj[i].size() == 1 && MaxBranch[i] == 0)
				sink(i, 1);
		// Sort (the indices of) the designs (in peril) in order of their branch length
		willsink = 0;
		for (i = 0; i < n; i++)
			if (MaxBranch[i] > 0)
				Idx[willsink++] = i;
		sort(Idx, Idx+willsink, cmp);

		// Place the spare boats
		for (q = willsink-1; q >= 0 && k > 0; q--)
		{	i = Idx[q]; // The design at which the longest branch starts
			if (MaxBranch[i] == 0) // Design was already saved
				continue;
			k--;
			willsink -= b = MaxBranch[i]; // We save all boats in the branch
			// Mark all designs in the branch as saved
			for (b--; true; b--)
			{	MaxBranch[i] = 0;
				if (b == 0) // Done!
					break;
				for (j = 0; MaxBranch[Child[i][j]] != b; j++); // Find child on the/a longest branch
				i = Child[i][j];
			}
		}
		printf("%d\n", willsink);
	}
	return 0;
}
