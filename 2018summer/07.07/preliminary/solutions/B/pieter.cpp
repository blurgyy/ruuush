// Solution to Failing components
// Author: Pieter Bootsma

// Time complexity: O(d log n)
// Memory: O(n + d)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: trace failures using dijkstra

#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_VER = 10005;

int n, d, c;

struct dependency
{
	int other;
	int time;
	
	dependency(int other, int time) : other(other), time(time) {}
};

struct component
{
	int failtime;
	vector<dependency> dependencies;
};

struct state
{
	int component;
	int time;
	
	state(int component, int time) : component(component), time(time) {}
	
	bool operator<(const state &other) const { return other.time < time; }
};

component components[MAX_VER];

void dostep()
{
	// Reset state
	for (int i = 0; i < MAX_VER; i++)
	{
		components[i].failtime = INT_MAX;
		components[i].dependencies.clear();
	}
	
	// Read input
	cin >> n >> d >> c;
	
	for (int i = 0; i < d; i++)
	{
		int a, b, s; // a depends on b => if b fails, a will fail after s seconds
		cin >> a >> b >> s;
		
		components[b].dependencies.emplace_back(dependency(a, s));
	}
	
	// Run Dijkstra
	priority_queue<state> pq;
	components[c].failtime = 0;
	pq.emplace(state(c, 0));
	while (!pq.empty())
	{
		state st = pq.top();
		pq.pop();
		if (components[st.component].failtime < st.time)
		{
			continue;
		}
		for (auto dependency : components[st.component].dependencies)
		{
			int newfailtime = components[st.component].failtime + dependency.time;
			if (newfailtime < components[dependency.other].failtime)
			{
				components[dependency.other].failtime = newfailtime;
				pq.emplace(state(dependency.other, newfailtime));
			}
		}
	}
	
	// Find number of failed components and max. fail time
	int nr_failed = 0;
	int max_time = 0;
	for (int i = 1; i <= n; i++)
	{
		if (components[i].failtime < INT_MAX)
		{
			nr_failed++;
			max_time = max(max_time, components[i].failtime);
		}
	}
	
	cout << nr_failed << ' ' << max_time << endl;
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
