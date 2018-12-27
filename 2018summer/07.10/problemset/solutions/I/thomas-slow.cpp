// Solution to Interesting Integers
// Author: Thomas Beuman

// Time complexity: O(nmax*log(nmax)*log(#cases)) (for all test cases)
// Memory: O(#cases)

// @EXPECTED_RESULTS@: TIMELIMIT

// Solution method: Brute force over a and b until all numbers in the test cases are encountered

#include <algorithm>
#include <cstdio>
#include <set>
#include <utility>
using namespace std;

const int runsmax = 1000000;

int n[runsmax];
pair<int,int> Answer[runsmax];
set<int> Input;

int main()
{	int runs, run, a, b, g, gp, t, done = 0, nmax = 0;

	// Read all input
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{	scanf("%d", &n[run]);
		Input.insert(n[run]);
		nmax = max(nmax, n[run]);
	}

	// Process all b in increasing order
	for (b = 1; true; b++)
		for (a = 0; a <= b/2; a++) // a=0 is equivalent to a=b
		{	gp = a;
			g = b;
			while (g <= nmax)
			{	if (Input.count(g)) // Check input
				{	for (run = 0; run < runs; run++)
						if (n[run] == g)
						{	Answer[run] = make_pair(a?a:b, b);
							fprintf(stderr, "Test cases solved: %d/%d\r", ++done, runs);
						}
					Input.erase(g);
					if (done == runs) // Print all answers
					{	fprintf(stderr, "\n");
						for (run = 0; run < runs; run++)
							printf("%d %d\n", Answer[run].first, Answer[run].second);
						return 0;
					}
				}
				t = g;
				g = g+gp;
				gp = t;
			}
		}
	return 0;
}
