// Solution to Highway Hassle
// Author: Thomas Beuman

// Time complexity: O(s*m*log(m))
// Memory: O(n*s)

// @EXPECTED_RESULTS@: WRONG-ANSWER

/* Solution method:
 *
 * Run a Dijkstra from every station to find the shortest path to all other stations.
 * Insight: consider going from station s1 to s2.
 *   - If s2 is cheaper than s1, then you want to get just enough petrol at s1 to reach s2.
 *   - If s1 is cheaper than s2, then you want to get a full tank at s1.
 * For each pair s1 -> s2 within distance d<t of each other, add an edge with length:
 *   - If p1 > p2: p1*d
 *   - If p1 < p2: p1*t - p2*(t-d)  (price of full tank - value of remaining petrol at p2)
 * Run a shortest path (Bellman-Ford) from c to d
 */

// This algorithm effectively allows for petrol to be exchanged back for money;
//   this can give negative cycles.

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int nmax = 1000, smax = 120;

int X[smax+1], P[smax+1], Dis[smax][nmax], Dis2[smax+1];
vector<int> Adj[nmax], Len[nmax];

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

int bellmanford (int start, int finish, int n, int D[])
{	int i, j, k;
	memset(D, 63, n*sizeof(int));
	D[start] = 0;
	for (i = 0; i < n-1; i++)
		for (j = 0; j < n; j++)
			for (k = Adj[j].size()-1; k >= 0; k--)
				D[Adj[j][k]] = min(D[Adj[j][k]], D[j] + Len[j][k]);
	return D[finish];
}

int main()
{	int runs, run, n, m, s, t, a, b, f, x, c, d, i, j, cs, dis;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %d %d", &n, &m, &s, &t);
		for (i = 0; i < n; i++)
		{	Adj[i].clear();
			Len[i].clear();
		}
		//printf("run %d\n", run);
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
		for (i = 0; i <= s; i++)
		{	Adj[i].clear();
			Len[i].clear();
		}
		// For all stations within reach of each other...
		for (i = 0; i < s; i++)
			for (j = 0; j <= s; j++)
				if (i != j && (dis = Dis[i][X[j]]) <= t)
				{	// If P[i] < P[j], get as much petrol as possible; otherwise, as little as possible
					Adj[i].push_back(j);
					Len[i].push_back(P[i] < P[j] ? P[i]*t - P[j]*(t-dis) : P[i]*dis);
				}
		// Find shortest path
		printf("%d\n", bellmanford(cs, s, s+1, Dis2));
	}
	return 0;
}
