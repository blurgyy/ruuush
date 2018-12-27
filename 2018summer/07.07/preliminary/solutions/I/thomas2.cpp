// Solution to Train Station Tunnel
// Author: Thomas Beuman

// Time complexity: O(l*n*log(n))
// Memory: O(n+w*l)

// @EXPECTED_RESULTS@: CORRECT

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;

const int nmax = 1000, wmax = 1000, lmax = 3000, tmax = 100000;

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

deque<person> TunnelRow[wmax+1];
int Occ[wmax+1][lmax+1];

int main()
{	int runs, run, l, w, n, x, y, s, i, m, t, xnew;
	char c;
	person *P;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d %d %d", &l, &w, &n);
		for (y = 0; y <= w; y++)
			TunnelRow[y].clear();
		for (i = 0; i < n; i++)
		{	scanf("%d %d %d %c", &x, &y, &s, &c);
			TunnelRow[y].push_back(person(x, s, c=='L' ? left : right));
		}
		memset(Occ, -1, sizeof(Occ));

		// Simulate
		for (t = 0; n > 0 && t < tmax; t++)
		{
			// Move right-moving people, from right to left
			for (y = 1; y <= w; y++)
			{	sort(TunnelRow[y].begin(), TunnelRow[y].end());
				m = TunnelRow[y].size();
				for (i = m-1; i >= 0; i--)
					if ((P = &TunnelRow[y][i])->dir == right)
					{	xnew = P->x + P->speed; // Desired destination
						// Check for collision inside tunnel
						if (i < m-1 && xnew >= TunnelRow[y][i+1].x)
						{	xnew = TunnelRow[y][i+1].x-1;
							P->annoyed = (xnew - P->x <= (P->speed+1)/2);
						}
						else
							P->annoyed = false;
						if (xnew > l) // Freedom!
						{	n--;
							TunnelRow[y].pop_back();
							m--;
						}
						else
						{	P->x = xnew;
							Occ[y][xnew] = t; // Occupied (t == true)
						}
					}
			}

			// Move left-moving people, from left to right
			for (y = 1; y <= w; y++)
			{	sort(TunnelRow[y].begin(), TunnelRow[y].end());
				m = TunnelRow[y].size();
				for (i = 0; i < m; i++)
					if ((P = &TunnelRow[y][i])->dir == left)
					{	xnew = P->x - P->speed; // Desired destination
						// Check for collision inside tunnel
						if (i > 0 && xnew <= TunnelRow[y][i-1].x)
						{	xnew = TunnelRow[y][i-1].x+1;
							P->annoyed = (P->x - xnew <= (P->speed+1)/2);
						}
						else
							P->annoyed = false;
						if (xnew < 1) // Freedom!
						{	n--;
							TunnelRow[y].pop_front();
							m--;
							i--;
						}
						else
						{	P->x = xnew;
							Occ[y][xnew] = t; // Occupied (t == true)
						}
					}
			}

			// Annoyed right-moving people going up
			for (y = 2; y <= w; y++)
				for (i = TunnelRow[y].size()-1; i >= 0; i--)
					if ((P = &TunnelRow[y][i])->dir == right && P->annoyed && Occ[y-1][P->x] != t)
					{	P->annoyed = false;
						Occ[y][P->x] = -1;
						Occ[y-1][P->x] = t;
						TunnelRow[y-1].push_back(*P);
						TunnelRow[y][i] = TunnelRow[y][0];
						TunnelRow[y].pop_front();
					}
			// Annoyed left-moving people going down
			for (y = w-1; y >= 1; y--)
				for (i = TunnelRow[y].size()-1; i >= 0; i--)
					if ((P = &TunnelRow[y][i])->dir == left && P->annoyed && Occ[y+1][P->x] != t)
					{	P->annoyed = false;
						Occ[y][P->x] = -1;
						Occ[y+1][P->x] = t;
						TunnelRow[y+1].push_back(*P);
						TunnelRow[y][i] = TunnelRow[y][0];
						TunnelRow[y].pop_front();
					}
			// Annoyed right-moving people going down
			for (y = w-1; y >= 1; y--)
				for (i = TunnelRow[y].size()-1; i >= 0; i--)
					if ((P = &TunnelRow[y][i])->dir == right && P->annoyed && Occ[y+1][P->x] != t)
					{	P->annoyed = false;
						Occ[y][P->x] = -1;
						Occ[y+1][P->x] = t;
						TunnelRow[y+1].push_back(*P);
						TunnelRow[y][i] = TunnelRow[y][0];
						TunnelRow[y].pop_front();
					}
			// Annoyed left-moving people going up
			for (y = 2; y <= w; y++)
				for (i = TunnelRow[y].size()-1; i >= 0; i--)
					if ((P = &TunnelRow[y][i])->dir == left && P->annoyed && Occ[y-1][P->x] != t)
					{	P->annoyed = false;
						Occ[y][P->x] = -1;
						Occ[y-1][P->x] = t;
						TunnelRow[y-1].push_back(*P);
						TunnelRow[y][i] = TunnelRow[y][0];
						TunnelRow[y].pop_front();
					}
		}

		if (t == tmax)
			fprintf(stderr, "This is taking too long!\n");
		// Print answer
		printf("%d\n", t);
	}
	return 0;
}
