// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
using std::pair;
#include <algorithm>
using std::swap;
using std::sort;
#include <stack>
using std::stack;

const int MAXN = 10000;
const int MAXM = 10000;

typedef pair<int,int> Edge;
typedef vector<Edge> Edges;
typedef long long int Report;
typedef vector<Report> Reports;

struct Vertex
{
  Edges::iterator inNeighbours, outNeighbours;
  Report report;
  int component;
};
const int NOTDISCOVERED = -2;
const int DISCOVERED = -1;

typedef vector<Vertex> Vertices;
typedef stack<int> VertexStack;
typedef pair<int, Edges::iterator> DFSBranch;
typedef stack<DFSBranch> DFSStack;

void filter(Report& a, Report b)
{
  if (a < b) swap(a, b);
  while (b != 0) { swap(a, b); b = b % a; } 
}

void solve()
{
  // read header
  int n, m; Report leakedReport;
  cin >> n >> m >> leakedReport;
    
  // read original edges and reversed edges 
  Edges forward(m+1);
  Edges reversed(m+1);
  for (int i = 0; i < m; ++i)
  {
    cin >> forward[i].first >> forward[i].second;
    --forward[i].first; --forward[i].second; // change counting to start from zero
    reversed[i].first = forward[i].second; reversed[i].second = forward[i].first;
  }
  // add sentinels
  forward[m].first = n;
  reversed[m].first = n;

  // sort edges by origin
  sort(forward.begin(), forward.end());
  sort(reversed.begin(), reversed.end());
  
  // create vertices and read old messages
  Vertices vertices(n);
  {
    Edges::iterator f = forward.begin(); Edges::iterator r = reversed.begin();
    for (int i = 0; i < n; ++i) 
    {
      vertices[i].outNeighbours = f; while (f->first == i) ++f; 
      vertices[i].inNeighbours = r;  while (r->first == i) ++r;
      cin >> vertices[i].report;
      vertices[i].component = NOTDISCOVERED;
    }
  }
  
  // DFS on original edges, marking vertices when discovered, pushing finished vertices on a stack
  VertexStack topologicalOrder;
  DFSStack DFSPath;
  for (int i = 0; i < n; ++i)
  {
    if (vertices[i].component == DISCOVERED) continue;
    DFSPath.push(DFSBranch(i, vertices[i].outNeighbours));
    while (!DFSPath.empty())
    {
      if (DFSPath.top().second->first != DFSPath.top().first)
      {
        topologicalOrder.push(DFSPath.top().first);
        DFSPath.pop();
        continue;
      }
      int head = DFSPath.top().second->second;
      if (vertices[head].component == DISCOVERED)
      {
        ++DFSPath.top().second;
        continue;
      }
      vertices[head].component = DISCOVERED;
      DFSPath.push(DFSBranch(head, vertices[head].outNeighbours));
    }
  }
      
  // pop vertices from stack, DFS on reversed edges from each unlabelled vertex to propagate labels,
  //    while counting number of vertices and component, and
  //    maintaining GGD (also including labels from components at other end of cross-edge in reversed graph)
  //    add vertices to count if GGD matches leaked label
  int suspects = 0;
  while (!topologicalOrder.empty())
  {
    int label = topologicalOrder.top();
    topologicalOrder.pop();
    if (vertices[label].component >= 0) continue;
    vertices[label].component = label;
    int componentSize = 1;
    DFSPath.push(DFSBranch(label, vertices[label].inNeighbours));
    while (!DFSPath.empty())
    {
      if (DFSPath.top().second->first != DFSPath.top().first)
      {
        DFSPath.pop();
        continue;
      }
      int tail = DFSPath.top().second->second;
      if (vertices[tail].component >= 0)
      {
        filter(vertices[label].report, vertices[vertices[tail].component].report);
        ++DFSPath.top().second;
        continue;
      }
      vertices[tail].component = label;
      ++componentSize;
      filter(vertices[label].report, vertices[tail].report);
      DFSPath.push(DFSBranch(tail, vertices[tail].inNeighbours));
    }
    if (vertices[label].report == leakedReport) suspects += componentSize;
  }
  
  cout << suspects << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

