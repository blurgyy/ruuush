// Solution to Floor Painting
// Author: Thomas Beuman

// Time complexity: O(n^2*log(n))
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * Divide the walls into horizontal and vertical.
 * Consider every bottom wall; let ymin be its y-coordinate.
 * First identify all vertical walls that run through y = ymin;
 *   these walls (alternatingly left and right) give intervals in which the painting can be.
 * Loop over all horizontal walls with a higher y-coordinate;
 *   update the intervals based on what x-range is blocked by the wall.
 * Every time a top wall is encountered, find the size dxmax of the largest interval.
 * The largest square that fits between the bottom and top wall is min(ytop-ymin, dxmax).
 * Keep track of the maximum.
 */

#include <algorithm>
#include <cstdio>
#include <queue>
#include <set>
#include <utility>
using namespace std;

const int nmax = 1000;

const int infty = 1<<30;
const int top = 0, bottom = 1;

// Horizontal wall
struct hwall
{	int type, x1, x2, y;
	hwall() {}
	hwall (int t, int a1, int a2, int b) : type(t), x1(a1), x2(a2), y(b) {}
};

// Vertical wall
struct vwall
{	int x, y1, y2;
	vwall() {}
	vwall (int a, int b1, int b2) : x(a), y1(b1), y2(b2) {}
};

bool operator < (hwall A, hwall B)
{	return A.y < B.y || (A.y == B.y && A.type < B.type);
}

bool operator < (vwall A, vwall B)
{	return A.x < B.x;
}

struct cmp
{	bool operator() (pair<int,int> A, pair<int,int> B)
	{	return A.second - A.first < B.second - B.first;
	}
};

int X[nmax], Y[nmax];
hwall Hwall[nmax/2];
vwall Vwall[nmax/2];
set<pair<int,int> > S;

int main()
{	int runs, run, n, i, j, x1, x2, dxmax, xprev, ymin, largestsquare;
	pair<int,int> P;
	set<pair<int,int> >::iterator it1, it2;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d %d", &X[i], &Y[i]);
		//if (run != 14) continue;

		// Organize the walls
		for (i = 0; i < n; i++)
		{	j = (i+1) % n;
			if (X[i] < X[j])
				Hwall[i/2] = hwall(top, X[i], X[j], Y[i]);
			else if (X[i] > X[j])
				Hwall[i/2] = hwall(bottom, X[j], X[i], Y[i]);
			else if (Y[i] < Y[j])
				Vwall[i/2] = vwall(X[i], Y[i], Y[j]);
			else if (Y[i] > Y[j])
				Vwall[i/2] = vwall(X[i], Y[j], Y[i]);
		}
		sort(Hwall, Hwall + n/2); // Sort by y-coordinate
		sort(Vwall, Vwall + n/2); // Sort by x-coordinate

		largestsquare = 0;
		// Loop over all bottom walls
		for (i = 0; i < n/2; i++)
			if (Hwall[i].type == bottom && Hwall[i].y < Hwall[i+1].y) // Consider each y at most once
			{	ymin = Hwall[i].y;
				S.clear(); // Intervals
				priority_queue<pair<int,int>, vector<pair<int,int> >, cmp> Q; // Intervals sorted by size

				// Identify all vertical walls that intersect y = ymin
				xprev = -1;
				for (j = 0; j < n/2; j++)
					if (Vwall[j].y1 <= ymin && Vwall[j].y2 > ymin)
					{	if (xprev == -1)
							xprev = Vwall[j].x;
						else
						{	P = make_pair(xprev, Vwall[j].x); // New interval
							S.insert(P);
							Q.push(P);
							xprev = -1;
						}
					}

				// Loop over all higher horizontal walls
				for (j = i+1; j < n/2 && !S.empty(); j++)
				{	if (Hwall[j].type == top) // Fit the painting
					{	while (!S.count(Q.top()))
							Q.pop(); // Throw away old rubbish
						dxmax = Q.top().second - Q.top().first; // Largest interval
						largestsquare = max(largestsquare, min(Hwall[j].y - ymin, dxmax)); // Update
						if (dxmax <= largestsquare) // dxmax can only decrease
							break;
					}

					// Update intervals
					x1 = Hwall[j].x1;
					x2 = Hwall[j].x2;
					// Check if x1 is inside an interval
					it1 = S.lower_bound(make_pair(x1, -infty));
					if (it1 != S.begin())
					{	it1--;
						if (x1 < it1->second) // Inside: create new interval
						{	P = make_pair(it1->first, x1);
							S.insert(P);
							Q.push(P);
						}
						else
							it1++;
					}
					// Check if x2 is inside an interval
					it2 = S.lower_bound(make_pair(x2, -infty));
					if (it2 != S.begin())
					{	it2--;
						if (x2 < it2->second) // Inside: create new interval
						{	P = make_pair(x2, it2->second);
							S.insert(P);
							Q.push(P);
						}
						it2++;
					}
					// Remove obsolete intervals
					while (it1 != it2)
						S.erase(it1++);
				}
			}

		// Print answer
		printf("%d\n", largestsquare);
	}
	return 0;
}
