// Solution to Talent Selection
// Author: Pieter Bootsma

// @EXPECTED_RESULTS@: CORRECT

// Solution method: binary search over the possible number of favorites to advance

#include <algorithm>
#include <iostream>

using namespace std;

const int MAX_CAND = 1e6+10;

int n, s, f, k;
int inpoints[MAX_CAND]; // points in input, first favorites then others
int points[MAX_CAND]; // actual points given, first favorites then others
int mypoints[MAX_CAND]; // points i can give

void dostep()
{
	// Read input
	cin >> n >> s >> f;
	
	// Read points given to favorites and others
	for (int i = 0; i < n; i++)
	{
		cin >> inpoints[i];
	}
	
	// Set all points to give to 0, then read actual points to give
	fill(mypoints, mypoints + n, 0);
	
	cin >> k;
	
	for (int i = 0; i < k; i++)
	{
		cin >> mypoints[i];
	}
	
	// Sort favorites and others in increasing order of points
	sort(inpoints, inpoints + f, less<int>());
	sort(inpoints + f, inpoints + n, less<int>());
	
	// Sort points to give in decreasing order of points
	sort(mypoints, mypoints + k, greater<int>());
	
	// Binary search over possible amounts of favorites to let advance
	int min = 0;
	int max = std::min(s, f) + 1; // Actually one over the maximum
	
	while (min < max - 1)
	{
		int target = (min + max) / 2;
		
		// Next element of mypoints to give out
		int next = 0;
		
		// Give points to target # of favorites with highest inpoints
		for (int i = f - target; i < f; i++)
		{
			points[i] = inpoints[i] + mypoints[next++];
		}
		// Give points to remaining favorites
		for (int i = f - target - 1; i >= 0; i--)
		{
			points[i] = inpoints[i] + mypoints[next++];
		}
		// Give points to most likely non-favorites to go through
		for (int i = n - (s - target); i < n; i++)
		{
			points[i] = inpoints[i] + mypoints[next++];
		}
		// Give points to remaining non-favorites
		for (int i = f; i < n - (target - s); i++)
		{
			points[i] = inpoints[i] + mypoints[next++];
		}
		
		// Sort favorites and others in decreasing order of points
		sort(points, points + f, greater<int>());
		sort(points + f, points + n, greater<int>());
		
		// Count number of advanced candidates
		int nf = 0;
		int no = 0;
		
		while ((nf + no < s) && (nf < f))
		{
			// Advance favorite if either there are no others left, or if the next favorite has
			// at least as many points as the next other to advance
			if ((no >= (n - f)) || (points[nf] >= points[f + no]))
			{
				nf++;
			}
			else
			{
				no++;
			}
		}
		
		if (nf >= target) // Can advance target number of favorites
		{
			min = nf;
		}
		else // Cannot advance target number of favorites
		{
			max = target;
		}
	}
	
	cout << min << endl;
}

int main(int, char**)
{
	int n;
	cin >> n;
	while (n--)
	{
		dostep();
	}
	
	return 0;
}
