// Solution to Spy Network
// Author: Thomas Beuman

// Time complexity: O(m*log(report))
// Memory: O(m)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * Identify the strongly connected components; in each component, all will have the same report.
 * Build a directed acyclic graph with the scc's as nodes; determine the (inital) report per scc.
 * Determine the final report per scc recursively by taking the greatest common divisor
 *   of the final reports of all the scc's with an outgoing edge to this scc.
 * Count the spies that are in a scc with l as its final report.
 */

#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

const int nmax = 10000, mmax = 10000;

long long Report[nmax], SccReport[nmax];
vector<int> Contact[nmax], SccEdge[nmax];
bool Seen[nmax];


// Tarjan's strongly connected components algorithm

const int unseen = 0, instack = 1, processed = 2;

int indexnr, nscc, Index[nmax], LowContact[nmax], Status[nmax], SccId[nmax];
stack<int> S;

void sccrec (int v)
{	Index[v] = LowContact[v] = indexnr++;
	S.push(v);
	Status[v] = instack;
	int w, j;
	for (j = 0; j < (int)Contact[v].size(); j++)
		if (Status[w = Contact[v][j]] != processed)
		{	if (Status[w] == 0)
				sccrec(w);
			LowContact[v] = min(LowContact[v], LowContact[w]);
		}
	if (LowContact[v] == Index[v])
	{	do
		{	SccId[w = S.top()] = nscc;
			Status[w] = processed;
			S.pop();
		}
		while (w != v);
		nscc++;
	}
}

void strongly_connected_components (int n)
{	memset(Status, unseen, sizeof(Status));
	indexnr = 0;
	nscc = 0;
	for (int i = 0; i < n; i++)
		if (Status[i] != processed)
			sccrec(i);
}

// Greatest common divisor
long long gcd (long long a, long long b)
{	return b ? gcd(b, a%b) : a;
}

// Recursively determines final report for component s
long long finalreport (int s)
{	if (Seen[s]) // Already processed
		return SccReport[s];
	Seen[s] = true;
	int k;
	// Process all incoming reports
	for (k = SccEdge[s].size()-1; k >= 0; k--)
		SccReport[s] = gcd(SccReport[s], finalreport(SccEdge[s][k]));
	return SccReport[s];
}

int main()
{	int runs, run, n, m, a, b, i, j, k, s, answer;
	long long l;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %lld", &n, &m, &l);
		for (i = 0; i < n; i++)
			Contact[i].clear();
		for (j = 0; j < m; j++)
		{	scanf("%d %d", &a, &b);
			Contact[a-1].push_back(b-1);
		}
		for (i = 0; i < n; i++)
			scanf("%lld", &Report[i]);

		// Identify strongly connect components (scc)
		strongly_connected_components(n);

		// Determine report per scc and identify connected scc's
		for (s = 0; s < nscc; s++)
		{	SccReport[s] = 0;
			SccEdge[s].clear();
		}
		for (i = 0; i < n; i++)
		{	s = SccId[i];
			SccReport[s] = gcd(SccReport[s], Report[i]);
			for (k = Contact[i].size()-1; k >= 0; k--)
				SccEdge[SccId[Contact[i][k]]].push_back(s); // Note: INcoming edge!
		}

		// Determine report per scc
		memset(Seen, false, sizeof(Seen));
		for (s = 0; s < nscc; s++)
			finalreport(s);

		// Check all spies
		answer = 0;
		for (i = 0; i < n; i++)
			if (SccReport[SccId[i]] == l)
				answer++;

		// Print answer
		printf("%d\n", answer);
	}
	return 0;
}
