// Solution to Avoiding the Apocalypse
// Author: Thomas Beuman

// Time complexity: O(s*t*p)
// Memory: O(s*t)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: create a node for every combination of location and time, find maximum flow

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const int nmax = 1000, tmax = 100;

const int nodesmax = (tmax+1)*nmax+1;
const int infty = 1<<30;

bool Medic[nmax];

map<int,int> Cap[nodesmax]; // Cap[i][j] = capacity of edge between i and j
int previous[nodesmax], q[nodesmax];

// Finds shortest path, false = no path
bool bfs (int source, int sink)
{	int cur, last = 1, i, j;
	map<int,int>::iterator it;
	memset(previous, -1, sizeof(previous));
	q[0] = source;
	previous[source] = source;
	for (cur = 0; cur < last; cur++)
	{	i = q[cur];
		for (it = Cap[i].begin(); it != Cap[i].end(); it++)
			if (previous[j = it->first] < 0 && it->second > 0)
			{	previous[j] = i;
				if (j == sink)
					return true;
				q[last++] = j;
			}
	}
	return false;
}

int maxflow (int source, int sink, int g)
{	int bot, flow = 0, i, j;
	while (flow < g && bfs(source, sink)) // Find augmenting path
	{	// Find bottleneck capacity
		bot = infty;
		for (j = sink; j != source; j = i)
			bot = min(bot, Cap[i = previous[j]][j]);
		// Send flow and update capacities
		for (j = sink; j != source; j = i)
		{	Cap[i = previous[j]][j] -= bot;
			Cap[j][i] += bot;
		}
		flow += bot;
	}
	return min(flow, g);
}

int main()
{	int runs, run, n, start, g, s, m, r, a, b, p, t, i, j, k, x, i1, i2, safety;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read parameters
		scanf("%d %d %d %d %d", &n, &start, &g, &s, &m);
		start--;
		memset(Medic, false, sizeof(Medic));
		// Read medical facilities
		for (i = 0; i < m; i++)
		{	scanf("%d", &x);
			Medic[x-1] = true;
		}
		// Initialize graph
		safety = (s+1)*n; // Create node (with largest index) representing safety
		for (i = 0; i <= safety; i++)
			Cap[i].clear();
		for (i = 0; i < n; i++)
		{	for (k = 0; k < s; k++)
			{	i1 = k*n+i; // k = time index, i = location
				i2 = i1+n;
				Cap[i1][i2] = g; // Edge representing waiting at node i
				Cap[i2][i1] = 0; // Reverse edge needed for maxflow
			}
		}
		// Read roads
		scanf("%d\n", &r);
		for (j = 0; j < r; j++)
		{	scanf("%d %d %d %d", &a, &b, &p, &t);
			a--;
			b--;
			for (k = t; k <= s; k++) // k = arrival time at b
			{	i1 = (k-t)*n+a;
				i2 = Medic[b] ? safety : k*n+b;
				Cap[i1][i2] += p;
				Cap[i2][i1] = 0; // Reverse edge needed for maxflow
			}
		}
		printf("%d\n", maxflow(start, safety, g));
	}
	return 0;
}
