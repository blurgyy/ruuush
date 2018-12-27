// @EXPECTED_RESULTS@: WRONG-ANSWER
// wrongly assumes first node is safe

// #define DEBUGGING
#ifdef DEBUGGING
#define REPORT(activity) cerr << activity << endl;
#else
#define REPORT(activity)
#endif

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
using std::sort;

const int firstDesign = 1;

typedef pair<int,int> Edge;
typedef vector<Edge> Edges;

struct Vertex
{
  Edges::iterator neighbours;
  bool discovered;
  bool safe;
  int value;
  int height;
  int highestChild;
};
const int NOTDISCOVERED = -2;
const int DISCOVERED = -1;

typedef vector<Vertex> Vertices;
typedef pair<int, Edges::iterator> DFSBranch;

void solve()
{
  REPORT("Reading input...")
  // read header
  int n, m, k; cin >> n >> m >> k;  
    
  // read edges 
  Edges edges(2*m+1);
  for (int i = 0; i < m; ++i)
  {
    cin >> edges[i].first >> edges[i].second;
    if (edges[i].first == edges[i].second)
    {
      cerr << "Boat attached to the same float left and right. Will it float or will it sink?" << endl;
      exit(1);
    }
    edges[i].first -= firstDesign; edges[i].second -= firstDesign;
    edges[m+i].first = edges[i].second; edges[m+i].second = edges[i].first;
  }
  // add sentinel
  edges[2*m].first = firstDesign + n;

  REPORT("Sorting...")
  // sort edges by origin
  sort(edges.begin(), edges.end());

  REPORT("Scanning for double edges...")
  for (Edges::iterator i = edges.begin(); i+1 != edges.end(); ++i)
  {
    if (*i != *(i+1)) continue;
    cerr << "Two boats attached to the same pair of floats. Will they keep each other afloat or not?" << endl;
    exit(1);
  }
  
  REPORT("Constructing graph...")  
  // create vertices 
  Vertices vertices(n);
  {
    Edges::iterator f = edges.begin(); 
    for (int i = 0; i < n; ++i) 
    {
      vertices[i].neighbours = f; 
      vertices[i].discovered = false;
      vertices[i].safe = false;
      vertices[i].height = -1;
      while (f->first == i) ++f; 
    }
  }
  
  vector<DFSBranch> DFSStack;
  int safeStart = 0; // THIS IS WRONG

  REPORT("DFS to find all safe nodes and highest children of unsafe nodes...")  
  // DFS to find all safe nodes, and heights for unsafe nodes
  DFSStack.push_back(DFSBranch(-1, edges.end())); // sentinel
  DFSStack.push_back(DFSBranch(safeStart, vertices[safeStart].neighbours));
  vertices[safeStart].discovered = true;
  vertices[safeStart].safe = true;
  int nrSafe = 1;
  while (true)
  {
    #ifdef DEBUGGING
    // for (int i = 0; i < DFSStack.size(); ++i) cerr << DFSStack[i].first << ' ';
    // cerr << "->" << DFSStack.back().second->second << endl;
    #endif
    if (DFSStack.back().second->first != DFSStack.back().first)
    {
      // record height and backtrack
      REPORT("backtrack")
      int child = DFSStack.back().first;
      int height = vertices[child].height + 1;
      DFSStack.pop_back();
      if (DFSStack.size() == 1) break;
      if (height > vertices[DFSStack.back().first].height)
      {
        vertices[DFSStack.back().first].height = height;
        vertices[DFSStack.back().first].highestChild = child;
      }
      ++DFSStack.back().second;
      continue;
    }
    int head = DFSStack.back().second->second;
    if (head == DFSStack[DFSStack.size()-2].first)
    {
      REPORT("Ignore parent")
      // ignore the parent
      ++DFSStack.back().second;
      continue;
    }
    if (vertices[head].discovered)
    {
      REPORT("Mark safe")
      #ifdef DEBUGGING
      for (vector<DFSBranch>::iterator i = DFSStack.begin()+1; i != DFSStack.end(); ++i)
        cout << i->first << ':' << vertices[i->first].safe << endl;
      #endif
      // found a back edge, mark whole stack as safe
      for (vector<DFSBranch>::reverse_iterator i = DFSStack.rbegin(); !(vertices[i->first].safe); ++i)
      {
        vertices[i->first].safe = true;
        ++nrSafe;
      }
      ++DFSStack.back().second;
      continue;
    }
    // recurse
    REPORT("recurse")
    vertices[head].discovered = true;
    vertices[head].height = 0;
    vertices[head].highestChild = -1;
    DFSStack.push_back(DFSBranch(head, vertices[head].neighbours));
  }
  // clean up
  for (Vertices::iterator i = vertices.begin(); i != vertices.end(); ++i) i->discovered = false;

  REPORT("DFS to find values of unsafe leaves...")  
  vector<int> values;
  // DFS to compute values; record negative to facilitate sorting in decreasing order
  DFSStack.push_back(DFSBranch(safeStart, vertices[safeStart].neighbours));
  vertices[safeStart].discovered = true;
  while (true)
  {
    if (DFSStack.back().second->first != DFSStack.back().first)
    {
      // backtrack
      DFSStack.pop_back();
      if (DFSStack.size() == 1) break;
      ++DFSStack.back().second;
      continue;
    }
    int head = DFSStack.back().second->second;
    if (head == DFSStack[DFSStack.size()-2].first || vertices[head].discovered)
    {
      // ignore parent and back edges
      ++DFSStack.back().second;
      continue;
    }
    // recurse
    if (vertices[DFSStack.back().first].safe || head != vertices[DFSStack.back().first].highestChild)
      vertices[head].value = 1;
    else
      vertices[head].value = 1 + vertices[DFSStack.back().first].value;
    if ((vertices[head].neighbours+1)->first != head) 
    {
      // not more than one edge, so only to parent, so it is a leaf
      values.push_back(-vertices[head].value);
      ++DFSStack.back().second;
      continue;
    }
    vertices[head].discovered = true;
    DFSStack.push_back(DFSBranch(head, vertices[head].neighbours));
  }
  
  #ifdef DEBUGGING
  for (int i = 0; i < vertices.size(); ++i)
    cout << i << ':' << vertices[i].safe << '/' << vertices[i].height << '/' << vertices[i].highestChild << '/' << vertices[i].value << endl;
  #endif
  
  REPORT("Sorting leaves...")  
  sort(values.begin(), values.end());
  REPORT(values.size() << endl)
  int sunk = n - nrSafe;
  for (int i = 0; i < k && i < values.size(); ++i) sunk += values[i];
  cout << sunk << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}


