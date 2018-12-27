// Solution to Floor Painting
// Author: Thomas Beuman

// Time complexity: O(n^2)
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT

/* Solution method:
 *
 * Divide the walls into top, bottom, left and right.
 * Consider the lowest bottom wall and the lowest top wall.
 * Loop over all walls in order of their (left) x-coordinate;
 *   consider only the ones that are (partly) between the top and bottom wall.
 * Find the maximum difference dxmax between a left and a right wall that are consecutive,
 *   with no (segment of) horizontal wall in between.
 * The largest square that fits between the top and bottom wall is min(ytop-ybottom, dxmax).
 * If ytop-ybottom <= dxmax, then there is no point in considering higher bottom walls:
 *   ytop-ybottom can only decrease. Continue with the next lowest top wall.
 * If dxmax <= ytop-ybottom, then there is no point in considering higher top walls:
 *   dxmax can only decrease. Continue with the next lowest bottom wall.
 */

#include <algorithm>
#include <cstdio>
using namespace std;

const int nmax = 1000;

const int infty = 1<<30;
enum{right, top, bottom, left}; // Order matters!

struct wall
{	int type, x1, x2, y1, y2;
	wall() {}
	wall (int t, int a1, int a2, int b1, int b2) : type(t), x1(a1), x2(a2), y1(b1), y2(b2) {}
};

bool operator < (wall A, wall B)
{	return A.x1 < B.x1 || (A.x1 == B.x1 && A.type < B.type);
}

bool cmp (wall A, wall B)
{	return A.y1 < B.y1;
}

int X[nmax], Y[nmax];
wall Wall[nmax], TopWall[nmax/2], BottomWall[nmax/2];

int main()
{	int runs, run, n, i, j, k, nb, nt, xmin, xblocked, ymin, ymax, dxmax, largestsquare;
	scanf("%d", &runs);
	for (run = 0; run < runs; run++)
	{
		// Read input
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d %d", &X[i], &Y[i]);

		// Organize the walls
		nb = nt = 0;
		for (i = 0; i < n; i++)
		{	j = (i+1) % n;
			if (X[i] < X[j])
				TopWall[nt++] = Wall[i] = wall(top, X[i], X[j], Y[i], Y[i]);
			else if (X[i] > X[j])
				BottomWall[nb++] = Wall[i] = wall(bottom, X[j], X[i], Y[i], Y[i]);
			else if (Y[i] < Y[j])
				Wall[i] = wall(left, X[i], X[i], Y[i], Y[j]);
			else if (Y[i] > Y[j])
				Wall[i] = wall(right, X[i], X[i], Y[j], Y[i]);
		}
		sort(Wall, Wall + n); // Sort by (left) x-coordinate
		sort(TopWall, TopWall + nt, cmp); // Sort by y-coordinate
		sort(BottomWall, BottomWall + nb, cmp); // Sort by y-coordinate

		largestsquare = 0;
		i = j = 0;
		while (i < nb && j < nt)
		{	ymin = BottomWall[i].y1;
			ymax = TopWall[j].y1;
			xmin = infty; // x-coordinate of last left wall
			xblocked = -infty; // Reach of horizontal wall
			dxmax = 0;
			for (k = 0; k < n; k++)
			{	if (Wall[k].y1 < ymax && Wall[k].y2 > ymin)
					switch (Wall[k].type)
					{	case left:
							if (Wall[k].x1 >= xblocked)
								xmin = Wall[k].x1;
							break;
						case right:
							if (Wall[k].x1 >= xblocked)
								dxmax = max(dxmax, Wall[k].x1 - xmin);
							xmin = infty; // Reset xmin
							break;
						case top: case bottom:
							xblocked = max(xblocked, Wall[k].x2);
							break;
					}
			}
			if (dxmax <= ymax-ymin)
			{	largestsquare = max(largestsquare, dxmax);
				i++;
			}
			if (ymax-ymin <= dxmax)
			{	largestsquare = max(largestsquare, ymax-ymin);
				j++;
			}
		}

		// Print answer
		printf("%d\n", largestsquare);
	}
	return 0;
}
