// SWERC 2016 - Cairo Corridor
// Author: Miguel Oliveira
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
using namespace std;
#define A(i, j) ((i) * 2 * C + (j) * 2)
#define B(i, j) (A(i, j) + 1)
const int MAX = 1010;
const int MAXV = MAX*MAX*2;
const int NORTH = 1;
const int SOUTH = 2;
const int EAST = 4;
const int WEST = 8;

int L, C;
char board[MAX][2*MAX], visited[MAXV];

struct Vertex {
  int border;
  vector<int> adj;
  void Clear() {
    border = 0;
    adj.clear();
  }
} graph[MAXV];

void AddEdge(char type1, int i, int j, char type2, int y, int x) {
  if (y < 0 || y >= L || x < 0 || x >= C ||
      board[i][type1 == 'A' ? j*2 : j*2+1] == '1' ||
      board[y][type2 == 'A' ? x*2 : x*2+1] == '1')
    return;
  int v1 = type1 == 'A' ? A(i, j) : B(i, j);
  int v2 = type2 == 'A' ? A(y, x) : B(y, x);
  graph[v1].adj.push_back(v2);
}
void FillBorders() {
  for (int j = 0; j < C; ++j) {
    graph[A(0, j)].border |= NORTH;
    if ((j & 1) == 0)
      graph[B(0, j)].border |= NORTH;

    graph[B(L-1, j)].border |= SOUTH;
    if ((j & 1) != (L & 1))
      graph[A(L-1, j)].border |= SOUTH;
  }
  for (int i = 0; i < L; ++i) {
    graph[A(i, 0)].border |= WEST;
    if (i & 1)
      graph[B(i, 0)].border |= WEST;

    graph[B(i, C-1)].border |= EAST;
    if ((i & 1) == (C & 1))
      graph[A(i, C-1)].border |= EAST;
  }
}
void BuildGraph() {
  for (int i = 0; i < L; ++i) {
    for (int j = 0; j < C; ++j) {
      graph[A(i,j)].Clear();
      graph[B(i,j)].Clear();
      // horizontal cell if i and j are both even or both odd.
      if ((i & 1) == (j & 1)) {
        // A(i, j) is adjacent to B(i, j), A(i+1, j), B(i-1, j), A(i, j-1), B(i, j-1)
        AddEdge('A', i, j, 'B', i-1, j  );
        AddEdge('A', i, j, 'B', i  , j  );
        AddEdge('A', i, j, 'B', i  , j-1);
        AddEdge('A', i, j, 'A', i+1, j  );
        AddEdge('A', i, j, 'A', i  , j-1);
        // B(i, j) is adjacent to A(i, j), A(i+1, j), B(i-1, j), A(i, j+1), B(i, j+1)
        AddEdge('B', i, j, 'B', i  , j+1);
        AddEdge('B', i, j, 'B', i-1, j  );
        AddEdge('B', i, j, 'A', i  , j  );
        AddEdge('B', i, j, 'A', i  , j+1);
        AddEdge('B', i, j, 'A', i+1, j  );
      } else {
        // A(i, j) is adjacent to A(i-1, j), B(i-1, j), B(i, j-1), A(i, j+1), B(i, j)
        AddEdge('A', i, j, 'A', i-1, j  );
        AddEdge('A', i, j, 'B', i-1, j  );
        AddEdge('A', i, j, 'B', i  , j-1);
        AddEdge('A', i, j, 'A', i  , j+1);
        AddEdge('A', i, j, 'B', i  , j  );
        // B(i, j) is adjacent to A(i, j), B(i, j-1), A(i+1, j), B(i+1, j), A(i, j+1)
        AddEdge('B', i, j, 'A', i  , j  );
        AddEdge('B', i, j, 'B', i  , j-1);
        AddEdge('B', i, j, 'A', i+1, j  );
        AddEdge('B', i, j, 'B', i+1, j  );
        AddEdge('B', i, j, 'A', i  , j+1);
      }
    }
  }
  FillBorders();
}


void GetComponent(int v, vector<int>& component) {
  visited[v] = true;
  component.push_back(v);
  for (auto w : graph[v].adj)
    if (!visited[w])
      GetComponent(w, component);
}

char dvis[MAXV];
void Dfs(int v, int& border) {
  dvis[v] = 1;
  border |= graph[v].border;
  for (auto w : graph[v].adj)
    if (!dvis[w])
      Dfs(w, border);
}
bool IsCorridor(vector<int>& component, int del_vertex) {
  for (auto c : component)  // just find one vertex other than del_vertex
    if (c != del_vertex) {
      int border = 0;
      for (auto w : component)
        dvis[w] = 0;
      dvis[del_vertex] = 1;
      Dfs(c, border);
      return border == 0xF;
    } 
  return false;
}
bool CheckComponent(vector<int>& component) {
  set<int> vertices_to_check;
  int border = 0, am_large_degree = 0, am_leaves = 0;
  for (auto v : component) {
    border |= graph[v].border;
    int degree = graph[v].adj.size();
    if (degree > 4)
      return false;
    else if (degree == 1) { // leaf
      if (++am_leaves > 4)
        return false;
      vertices_to_check.insert(v);
    } else if (degree > 2) {
      if (++am_large_degree > 6)
        return false;
      vertices_to_check.insert(v);
      vertices_to_check.insert(graph[v].adj.begin(), graph[v].adj.end());
    }
  }
  if (border != 0xF)
    return false;
  for (auto v : vertices_to_check) 
    if (IsCorridor(component, v)) 
      return false;
  return true;
}

int Check(int v) {
  vector<int> component;
  GetComponent(v, component);
  if (CheckComponent(component))
    return component.size();
  return -1;
}

int Solve() {
  int answer = -1, nvertices = L * C * 2;
  memset(visited, 0, sizeof visited);
  for (int i = 0; i < nvertices; ++i) 
    if (!visited[i] && (answer = Check(i)) != -1)
      return answer;
  return answer;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &L, &C);
    for (int i = 0; i < L; ++i)
      scanf("%s", board[i]);
    BuildGraph();
    int answer = Solve();
    if (answer == -1)   
      puts("NO MINIMAL CORRIDOR");
    else
      printf("%d\n", answer);
  }
  return 0;
}
