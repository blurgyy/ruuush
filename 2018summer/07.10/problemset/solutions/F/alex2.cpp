// Solution to Floating Formation
// Author: Alex ten Brink

// Time complexity: O(n log n + m)
// Memory: O(n + m)

// @EXPECTED_RESULTS@: CORRECT

#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

#define DEBUG false

struct GainInfo
{
    int gain;
    bool disabled;
};
bool operator <(const GainInfo& left, const GainInfo& right)
{
    return left.gain < right.gain;
}

int main()
{
	int runs;
	cin >> runs;
	while (runs > 0)
	{
        int n, m, k;
        cin >> n >> m >> k;
        if (n > 10000) { cerr << "Too many vertices" << endl; exit(1); }
        if (m > 10000) { cerr << "Too many edges" << endl; exit(1); }
        if (k > 10000) { cerr << "Too many spare boats" << endl; exit(1); }

        vector<int> edges[n];

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            if (a > n || a < 1 || b > n || b < 1) { cerr << "Edge out of range" << endl; exit(1); }
            edges[a-1].push_back(b-1);
            edges[b-1].push_back(a-1);
        }

        int degreeaftersinking[n];
        stack<int> treestack;
        for (int i = 0; i < n; i++)
        {
            degreeaftersinking[i] = edges[i].size();
            if (degreeaftersinking[i] == 1) treestack.push(i);
        }
        while (treestack.size() > 0)
        {
            int next = treestack.top();
            treestack.pop();
            for (unsigned int i = 0; i < edges[next].size(); i++)
            {
                int neighbor = edges[next][i];
                if (degreeaftersinking[neighbor] > 1)
                {
                    degreeaftersinking[neighbor]--;
                    if (degreeaftersinking[neighbor] == 1)
                    {
                        treestack.push(neighbor);
                    }
                }
            }
        }

        int sizeof2core = 0;
        bool marked[n];
        GainInfo gains[n];
        for (int i = 0; i < n; i++)
        {
            gains[i].disabled = true;
            gains[i].gain = -1;
            marked[i] = false;
        }
        for (int i = 0; i < n; i++)
        {
            if (DEBUG) { cout << i << " has degree " << degreeaftersinking[i] << endl; }
            if (degreeaftersinking[i] > 1)
            {
                // Found potential root vertex
                sizeof2core++;
                // We push vertices on totalstack in such a way that all children
                // of a node are higher on the stack than their parents
                stack<int> workingstack;
                stack<int> totalstack;
                workingstack.push(i);
                marked[i] = true;
                while (!workingstack.empty())
                {
                    int current = workingstack.top();
                    workingstack.pop();
                    for (unsigned int j = 0; j < edges[current].size(); j++)
                    {
                        int neighbor = edges[current][j];
                        if (!marked[neighbor] && degreeaftersinking[neighbor] == 1)
                        {
                            workingstack.push(neighbor);
                            marked[neighbor] = true;
                        }
                    }
                    totalstack.push(current); if (DEBUG) { cout << "Pushing " << current << endl; }
                }
                while (!totalstack.empty())
                {
                    int current = totalstack.top();
                    totalstack.pop();
                    int maxofchildren = 0;
                    int indexofmax = 0;
                    for (unsigned int j = 0; j < edges[current].size(); j++)
                    {
                        int neighbor = edges[current][j];
                        if (degreeaftersinking[neighbor] == 1 && gains[neighbor].gain > maxofchildren)
                        {
                            maxofchildren = gains[neighbor].gain;
                            indexofmax = neighbor;
                        }
                    }
                    gains[current].gain = maxofchildren + (degreeaftersinking[current] == 1 ? 1 : 0); if (DEBUG) { cout << current << " will gain us " << maxofchildren + 1 << endl; }
                    gains[current].disabled = false;
                    if (maxofchildren > 0) { gains[indexofmax].disabled = true; if (DEBUG) { cout << "Disabled " << indexofmax << endl; } }
                }
            }
        }

        sort(gains, gains+n);
        int saveddesigns = 0;
        int index = n;
        for (int i = 0; i < k; i++)
        {
            do
            {
                index--;
            }
            while (index >= 0 && gains[index].disabled);
            if (index < 0) break;
            saveddesigns += gains[index].gain; if (DEBUG) { cout << "Using " << index << " which will help us " << gains[index].gain << endl; }
        }

        if (DEBUG) { cout << "Coresize " << sizeof2core << ", saveddesigns " << saveddesigns << endl; }
        cout << (n - sizeof2core - saveddesigns) << endl;

		runs--;
	}
	return 0;
}
