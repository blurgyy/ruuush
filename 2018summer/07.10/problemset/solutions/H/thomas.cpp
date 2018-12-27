// Solution to Highway Hassle
// Author: Thomas Beuman

// Time complexity: O(s*m*log(m)+s^2*log(s))
// Memory: O(n*s)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * Run a Dijkstra from every station to find the shortest path to all other stations.
 * Naive idea:
 *   Make a new graph with a node for every combination (s,p) of station and petrol amount.
 *   Add an edge between all nodes (s,p)->(s,p+1) with the corresponding price as length.
 *   Add an edge between all nodes (s1,p+d)->(s2,p), where d is the distance, with no length.
 *   Run a dijkstra from (c,0) to (d,0).
 * This fails because there are way too many amounts of petrol.
 * Insight: consider going from station s1 to s2.
 *   - If s2 is cheaper than s1, then you want to get just enough petrol at s1 to reach s2.
 *   - If s1 is cheaper than s2, then you want to get a full tank at s1.
 *   This means that, for each station, there are at most 2s relevant amounts of petrol
 *     (for each other station, one for arrival from and one for departure to).
 *   Now there are only O(s^2) nodes and O(s^2) edges.
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>
using namespace std;

const int nmax = 1000, smax = 120;

const int infty = 1<<30;

int X[smax+1], P[smax+1], Dis[smax][nmax], Dis2[2*smax*smax];
vector<int> Adj[2*smax*smax], Len[2*smax*smax];
map<int,int> T[smax+1];

struct node
{	int k, dis;
	node (int a, int b): k(a), dis(b) {}
};

bool operator < (const node &a, const node &b)
{	return a.dis > b.dis;
}

void dijkstra (int start, int n, int maxdis, int D[])
{	int i, j, k, dis, dis2;
	priority_queue<node> pq;
	memset(D, 63, n*sizeof(int));
	D[start] = 0;
	pq.push(node(start, 0));
	while (!pq.empty())
	{	k = pq.top().k;
		dis = pq.top().dis;
		pq.pop();
		if (D[k] < dis)
			continue;
		for (i = Adj[k].size()-1; i >= 0; i--)
			if ((dis2 = dis + Len[k][i]) <= maxdis && D[j = Adj[k][i]] > dis2)
				pq.push(node(j, D[j] = dis2));
	}
}

int main()
{	int runs, run, n, m, s, t, a, b, f, x, c, d, i, j, cs, dis;
	map<int,int>::iterator it, it2;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %d %d", &n, &m, &s, &t);
		for (i = 0; i < n; i++)
		{	Adj[i].clear();
			Len[i].clear();
		}
		for (j = 0; j < m; j++)
		{	scanf("%d %d %d", &a, &b, &f);
			Adj[a-1].push_back(b-1);
			Adj[b-1].push_back(a-1);
			Len[a-1].push_back(f);
			Len[b-1].push_back(f);
		}
		for (i = 0; i < s; i++)
		{	scanf("%d %d", &x, &P[i]);
			X[i] = x-1;
		}
		scanf("%d %d", &c, &d);

		// Find station at start node
		for (i = 0; i < s && X[i] != c-1; i++);
		cs = i;
		// Add station with free petrol at end node
		X[s] = d-1;
		P[s] = 0;
		// Find shortest path from every station to all nodes within reach
		for (i = 0; i < s; i++)
			dijkstra(X[i], n, t, Dis[i]);
		// Create nodes (station,fuel)
		for (i = 0; i <= s; i++)
			T[i].clear();
		// Add a node for the start with zero fuel
		T[cs][0] = 0;
		// For all stations within reach of each other...
		for (i = 0; i < s; i++)
			for (j = 0; j <= s; j++)
				if (i != j && (dis = Dis[i][X[j]]) <= t)
				{	// If P[i] < P[j], get as much petrol as possible; otherwise, as little as possible
					T[i][P[i] < P[j] ? t : dis] = 0;
					T[j][P[i] < P[j] ? t-dis : 0] = 0;
				}
		// Assign unique id's to all nodes
		n = 0;
		for (i = 0; i <= s; i++)
		{	for (it = T[i].begin(); it != T[i].end(); it++)
				it->second = n++;
		}
		for (i = 0; i < n; i++)
		{	Adj[i].clear();
			Len[i].clear();
		}
		// For every station, add an edge between all fuel nodes with corresponding price
		for (i = 0; i < s; i++)
			if (!T[i].empty())
				for (it = it2 = T[i].begin(), it2++; it2 != T[i].end(); it = it2++)
				{	Adj[it->second].push_back(it2->second);
					Len[it->second].push_back(P[i] * (it2->first - it->first));
				}
		// Add an edge for all stations within reach of each other
		for (i = 0; i < s; i++)
			for (j = 0; j <= s; j++)
				if (i != j && (dis = Dis[i][X[j]]) <= t)
				{	a = T[i][P[i] < P[j] ? t : dis];
					b = T[j][P[i] < P[j] ? t-dis : 0];
					Adj[a].push_back(b);
					Len[a].push_back(0);
				}
		// Find shortest path
		dijkstra(T[cs][0], n, infty, Dis2);
		printf("%d\n", Dis2[n-1]);
	}
	return 0;
}
