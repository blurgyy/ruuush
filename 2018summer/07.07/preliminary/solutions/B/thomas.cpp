// Solution to Failing Components
// Author: Thomas Beuman

// Time complexity: O(n*log(n))
// Memory: O(n+d)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: Dijkstra with heap

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int nmax = 100000, dmax = 1000000;

const int infty = 1<<30;

vector<int> Adj[nmax], Len[nmax];
int Dis[nmax];

struct node
{	int k, dis;
	node (int a, int b): k(a), dis(b) {}
};

bool operator < (const node &a, const node &b)
{	return a.dis > b.dis;
}

void dijkstra (int start, int n)
{	int i, j, k, dis;
	priority_queue<node> pq;
	for (i = 0; i < n; i++)
		Dis[i] = infty;
	Dis[start] = 0;
	pq.push(node(start, 0));
	while (!pq.empty())
	{	k = pq.top().k;
		dis = pq.top().dis;
		pq.pop();
		if (Dis[k] < dis)
			continue;
		for (i = Adj[k].size()-1; i >= 0; i--)
			if (Dis[j = Adj[k][i]] > dis + Len[k][i])
				pq.push(node(j, Dis[j] = dis + Len[k][i]));
	}
}

int main()
{	int runs, run, n, d, c, a, b, s, i, m, t;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %d", &n, &d, &c);
		for (i = 0; i < n; i++)
		{	Adj[i].clear();
			Len[i].clear();
		}
		for (i = 0; i < d; i++)
		{	scanf("%d %d %d", &a, &b, &s);
			Adj[b-1].push_back(a-1);
			Len[b-1].push_back(s);
		}

		dijkstra(c-1, n); // Shortest path algorithm
		// Find failed components
		m = 0;
		t = 0;
		for (i = 0; i < n; i++)
			if (Dis[i] < infty)
			{	m++;
				t = max(t, Dis[i]);
			}

		// Print answer
		printf("%d %d\n", m, t);
	}
	return 0;
}
