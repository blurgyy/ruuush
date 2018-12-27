// Solution to Train Station Tunnel
// Author: Thomas Beuman

// Time complexity: O(l*n*log(n))
// Memory: O(n+w)

// @EXPECTED_RESULTS@: CORRECT

#include <cstdio>
#include <set>
using namespace std;

const int nmax = 1000, wmax = 1000, tmax = 100000;

const int right = 1, left = -1;

struct person
{	int x, speed, dir;
	bool annoyed;
	person() {}
	person (int x0, int s0, int d0) : x(x0), speed(s0), dir(d0), annoyed(false) {}
};

bool operator < (person A, person B)
{	return A.x < B.x;
}

set<person> TunnelRow[wmax+1];

int main()
{	int runs, run, l, w, n, x, y, s, i, t, xnew;
	char c;
	person P;
	set<person>::iterator it, itprev, itnext;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %d", &l, &w, &n);
		for (y = 0; y <= w; y++)
			TunnelRow[y].clear();
		for (i = 0; i < n; i++)
		{	scanf("%d %d %d %c", &x, &y, &s, &c);
			TunnelRow[y].insert(person(x, s, c=='L' ? left : right));
		}

		// Simulate
		for (t = 0; n > 0 && t < tmax; t++)
		{
			// Move right-moving people, from right to left
			for (y = 1; y <= w; y++)
				if (!TunnelRow[y].empty())
					for (it = TunnelRow[y].end(), it--; it != TunnelRow[y].end(); it = itnext)
					{	// Determine previous (right) and next person (left neighbor)
						itnext = itprev = it;
						itprev++;
						if (it == TunnelRow[y].begin())
							itnext = TunnelRow[y].end();
						else
							itnext--;
						if (it->dir == right)
						{	P = *it;
							xnew = P.x + P.speed; // Desired destination
							// Check for collision inside tunnel
							if (itprev != TunnelRow[y].end() && xnew >= itprev->x)
							{	xnew = itprev->x-1;
								P.annoyed = (xnew - P.x <= (P.speed+1)/2);
							}
							else
								P.annoyed = false;
							TunnelRow[y].erase(it); // Remove
							if (xnew > l) // Freedom!
								n--;
							else // Reinsert
							{	P.x = xnew;
								TunnelRow[y].insert(P);
							}
						}
					}

			// Move left-moving people, from left to right
			for (y = 1; y <= w; y++)
				if (!TunnelRow[y].empty())
					for (it = TunnelRow[y].begin(); it != TunnelRow[y].end(); it = itnext)
					{	// Determine previous (left) and next person (right neighbor)
						itnext = itprev = it;
						if (it != TunnelRow[y].begin())
							itprev--;
						itnext++;
						if (it->dir == left)
						{	P = *it;
							xnew = P.x - P.speed; // Desired destination
							// Check for collision inside tunnel
							if (it != TunnelRow[y].begin() && xnew <= itprev->x)
							{	xnew = itprev->x+1;
								P.annoyed = (P.x - xnew <= (P.speed+1)/2);
							}
							else
								P.annoyed = false;
							TunnelRow[y].erase(it); // Remove
							if (xnew < 1) // Freedom!
								n--;
							else // Reinsert
							{	P.x = xnew;
								TunnelRow[y].insert(P);
							}
						}
					}

			// Annoyed right-moving people going up
			for (y = 2; y <= w; y++)
				for (it = TunnelRow[y].begin(); it != TunnelRow[y].end();)
				{	if (it->dir == right && it->annoyed && !TunnelRow[y-1].count(*it))
					{	P = *it;
						P.annoyed = false;
						TunnelRow[y-1].insert(P);
						TunnelRow[y].erase(it++);
					}
					else
						it++;
				}
			// Annoyed left-moving people going down
			for (y = w-1; y >= 1; y--)
				for (it = TunnelRow[y].begin(); it != TunnelRow[y].end();)
				{	if (it->dir == left && it->annoyed && !TunnelRow[y+1].count(*it))
					{	P = *it;
						P.annoyed = false;
						TunnelRow[y+1].insert(P);
						TunnelRow[y].erase(it++);
					}
					else
						it++;
				}
			// Annoyed right-moving people going down
			for (y = w-1; y >= 1; y--)
				for (it = TunnelRow[y].begin(); it != TunnelRow[y].end();)
				{	if (it->dir == right && it->annoyed && !TunnelRow[y+1].count(*it))
					{	P = *it;
						P.annoyed = false;
						TunnelRow[y+1].insert(P);
						TunnelRow[y].erase(it++);
					}
					else
						it++;
				}
			// Annoyed left-moving people going up
			for (y = 2; y <= w; y++)
				for (it = TunnelRow[y].begin(); it != TunnelRow[y].end();)
				{	if (it->dir == left && it->annoyed && !TunnelRow[y-1].count(*it))
					{	P = *it;
						P.annoyed = false;
						TunnelRow[y-1].insert(P);
						TunnelRow[y].erase(it++);
					}
					else
						it++;
				}
		}

		if (t == tmax)
			fprintf(stderr, "This is taking too long!\n");
		// Print answer
		printf("%d\n", t);
	}
	return 0;
}
