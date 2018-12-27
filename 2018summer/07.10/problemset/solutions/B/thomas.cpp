// Solution to Button Bashing
// Author: Thomas Beuman

// Time complexity: O(3600*n)
// Memory: O(n+3600)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: breadth-first search

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nmax = 16, tmax = 3600;

int B[nmax];

int BFS[tmax+1], Presses[tmax+1];
bool Seen[tmax+1];

int main()
{	int runs, run, n, t, i, k, k2, cur, last;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d", &n, &t);
		for (i = 0; i < n; i++)
			scanf("%d", &B[i]);

		memset(Seen, false, sizeof(Seen));
		Seen[0] = true;
		BFS[0] = 0;
		Presses[0] = 0;
		last = 1;
		for (cur = 0; cur < last; cur++)
		{	k = BFS[cur];
			for (i = 0; i < n; i++)
			{	k2 = min(tmax, max(0, k+B[i]));
				if (!Seen[k2])
				{	Seen[k2] = true;
					Presses[k2] = Presses[k] + 1;
					BFS[last++] = k2;
				}
			}
		}
		for (k = t; !Seen[k]; k++); // Find smallest reachable time > t
		printf("%d %d\n", Presses[k], k-t);
	}
	return 0;
}
