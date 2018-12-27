// Solution to Dropping Directions
// Author: Thomas Beuman

// Time complexity: O(n)
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * The network can be decomposed into loops.
 * For every loop that does not contain the goal, we need a signpost to redirect the people on it.
 * It is possible to direct everyone to the goal with one signpost for every such loop.
 * The answer is thus the number of loops that do not contain the goal.
 */

#include <cstdio>
#include <cstring>
using namespace std;

const int nmax = 100000;

int Neighbour[nmax+1][4];

bool Seen[nmax+1][2];

int main()
{	int runs, run, n, g, i, j, k, p;
	bool passedgoal;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d ", &n, &g);
		for (i = 1; i <= n; i++)
			for (j = 0; j < 4; j++)
				scanf("%d", &Neighbour[i][j]);

		// Count loops
		p = 0;
		memset(Seen, false, sizeof(Seen));
		for (i = 1; i <= n; i++)
			for (j = 0; j < 2; j++) // j = direction
				if (!Seen[i][j])
				{	passedgoal = false;
					while (!Seen[i][j&1]) // Continue until we are back
					{	Seen[i][j&1] = true;
						if (i == g)
							passedgoal = true;
						// Find next intersection
						k = Neighbour[i][j];
						for (j = 0; j < 4 && Neighbour[k][j] != i; j++);
						if (j == 4)
						{	fprintf(stderr, "Something is wrong!\n");
							return 0;
						}
						i = k;
						j ^= 2;
					}
					if (!passedgoal) // If we didn't pass the goal, we need another signpost
						p++;
				}
		printf("%d\n", p);
	}
	return 0;
}
