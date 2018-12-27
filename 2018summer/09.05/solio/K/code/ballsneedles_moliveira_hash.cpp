// SWERC 2016 - Balls of Wool and Needles
// Author: Miguel Oliveira
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
using namespace std;
const int MAX = 200100;

struct Graph {
  int nvertices = 0;
  vector<int> adj[MAX];
  unordered_map<int, int> indices;
  unordered_set<long long> edges_list;
  
  int GetIndex(int x, int y, int z) {
    int t = x * 1e6 + y * 1e3 + z;
    auto it = indices.find(t);
    if (it != indices.end())
      return it->second;
    return indices[t] = nvertices++;
  }

  void AddEdge(int x, int y, int z, int x2, int y2, int z2) {
    int a = GetIndex(x, y, z);
    int b = GetIndex(x2, y2, z2);
    if (a > b)
      swap(a, b);
    long long pp = (long long)a * MAX + b;
    if (a == b || edges_list.find(pp) != edges_list.end())
      return;
    adj[a].push_back(b);
    adj[b].push_back(a);
    edges_list.insert(pp);
  }

  bool HasCycle(int i, int parent, vector<bool>& visited) {
    visited[i] = true;
    for (auto w : adj[i])
      if (w != parent && (visited[w] || HasCycle(w, i, visited)))
        return true;
    return false;
  }
  bool HasCycle() {
    vector<bool> visited(nvertices, false);
    for (int i = 0; i < nvertices; ++i)
      if (!visited[i] && HasCycle(i, -1, visited))
          return true;
    return false;
  }
} graph3d, graph2d;

int main() {
  int K, x, y, z, x2, y2, z2;
  scanf("%d", &K);
  while (K--) {
    scanf("%d %d %d %d %d %d", &x, &y, &z, &x2, &y2, &z2);
    graph3d.AddEdge(x, y, z, x2, y2, z2);
    graph2d.AddEdge(x, y, 0, x2, y2, 0);
  }
  if (graph3d.HasCycle()) {
    puts("True closed chains");
  } else {
    puts("No true closed chains");
  }
  if (graph2d.HasCycle()) {
    puts("Floor closed chains");
  } else {
    puts("No floor closed chains");
  }
  return 0;
}
