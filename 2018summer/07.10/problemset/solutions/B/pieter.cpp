// Solution to Button Bashing
// Author: Pieter Bootsma

// Time complexity: O(Tn log T)
// Memory: O(Tn)
// T = max. number of seconds (3600)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: construct a graph with all achievable times as vertices,
//                  and all possible button presses as edges; then use
//                  single-source shortest path to find the minimum number
//                  of button presses for each time

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_VER = 3605;
const int INFINITE = 123456;

struct vertex
{
	vector<int> edges;
	int distance;
};

vertex vertices[MAX_VER];

void reset()
{
	for (int i = 0; i < MAX_VER; i++)
	{
		vertices[i].edges.clear();
		vertices[i].distance = INFINITE;
	}
}

// pair of (distance, vertex)
typedef pair<int, int> pp;

void dijkstra(int source)
{
	priority_queue<pp, vector<pp>, greater<pp> > q;
	vertices[source].distance = 0;
	q.push(make_pair(0, source));
	
	while (!q.empty())
	{
		int u = q.top().second;
		int distance = q.top().first;
		q.pop();
		
		if (distance > vertices[u].distance)
		{
			continue;
		}
		
		for (size_t i = 0; i < vertices[u].edges.size(); i++)
		{
			int v = vertices[u].edges[i];
			if (distance + 1 < vertices[v].distance)
			{
				vertices[v].distance = distance + 1;
				q.push(make_pair(vertices[v].distance, v));
			}
		}
	}
}

void dostep()
{
	// Initialize/reset graph
	reset();
	
	// Read input
	int nr_buttons;
	int target_time;
	cin >> nr_buttons >> target_time;
	
	// Add edges for each button while reading it
	for (int i = 0; i < nr_buttons; i++)
	{
		int button;
		cin >> button;
		
		// Loop over all vertices that this button can be pressed from
		for (int this_time = 0; this_time <= 3600; this_time++)
		{
			// Determine new time after button was pressed starting from this time
			int new_time = this_time + button;
			if (new_time < 0)
			{
				new_time = 0;
			}
			else if (new_time > 3600)
			{
				new_time = 3600;
			}
			
			// Otherwise, add edge
			vertices[this_time].edges.push_back(new_time);
		}
	}
	
	// Run dijkstra on constructed graph, starting from initial time (0s)
	dijkstra(0);
	
	// Figure out first achievable time, and print that time
	for (int i = 0; i < MAX_VER - target_time; i++)
	{
		int this_time = target_time + i;
		
		if (vertices[this_time].distance < INFINITE)
		{
			cout << vertices[this_time].distance << ' ' << i << endl;
			return;
		}
	}
	
	// This part should not be reached; but if we do, print validly formatted
	// output just to ensure that further test cases are not compromised
	cout << "-1 -1" << endl;
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
