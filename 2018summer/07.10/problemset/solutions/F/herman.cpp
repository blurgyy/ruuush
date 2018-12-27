// @EXPECTED_RESULTS@: CORRECT

/**********************************************************************
**  This code implements a solution to the afloat problem in         **
**  O(m log m) time and O(m) space                                   **
**                                                                   **                             
**  (log factor could be removed by using linear-time sorting)       **
**  For explanation of the algorithm see end of file                 **
**********************************************************************/

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
#include <stack>
using std::stack;

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
  
  REPORT("Verifying that the graph is connected...")
  stack<int> toExplore;
  toExplore.push(0); 
  while (!toExplore.empty())
  {
    int i = toExplore.top();
    toExplore.pop();
    if (vertices[i].discovered) continue;
    vertices[i].discovered = true; 
    for (Edges::iterator j = vertices[i].neighbours; j->first == i; ++j)
      toExplore.push(j->second);
  }
  // clean up
  for (int i = 0; i < vertices.size(); ++i)
  {
    if (!vertices[i].discovered) 
      cout << "There is no path from vertex 1 to vertex " << i+1 << endl;
    vertices[i].discovered = false;
  }

  REPORT("DFS to find a safe cycle to start from...")  
  // DFS to find a back edge = safe cycle to start from
  vector<DFSBranch> DFSStack;
  DFSStack.push_back(DFSBranch(-1, edges.end())); // sentinel
  DFSStack.push_back(DFSBranch(0, vertices[0].neighbours));
  vertices[0].discovered = true;
  int safeStart;
  while (true)
  {
    REPORT(DFSStack.back().first << ':' << DFSStack.back().second->first << '>' << DFSStack.back().second->second)
    if (DFSStack.back().second->first != DFSStack.back().first)
    {
      REPORT("backtrack")
      // backtrack
      vertices[DFSStack.back().first].discovered = false;
      DFSStack.pop_back();
      if (DFSStack.size() == 1) break; // should not happen
      ++DFSStack.back().second;
      continue;
    }
    int head = DFSStack.back().second->second;
    if (head == DFSStack[DFSStack.size()-2].first) 
    {
      REPORT("parent")
      // ignore the parent
      ++DFSStack.back().second;
      continue;
    }
    if (vertices[head].discovered)
    {
      REPORT("cycle found")
      // found a cycle
      safeStart = head;
      break;
    }
    REPORT("recurse")
    vertices[head].discovered = true;
    DFSStack.push_back(DFSBranch(head, vertices[head].neighbours));
  }
  REPORT("safe start " << safeStart)
  // clean up
  while (DFSStack.size() > 1)
  {
    vertices[DFSStack.back().first].discovered = false;
    DFSStack.pop_back();
  }      

  REPORT("DFS to find all safe nodes and highest children of unsafe nodes...")  
  // DFS to find all safe nodes, and heights for unsafe nodes
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

/*
Nodes on cycles are safe. A node not on a cycle is safe if and only if 
it has a safe ancestor and a safe descendant in a DFS tree, or 
multiple safe descendants. The problem is indeed simplified greatly by 
the fact that at least one design is known to stay afloat even without 
spare boats, and there is a single connected component. This means 
that there is at least one cycle, and if we do DFS from a node on that
cycle, every node has a safe ancestor, and the discovery of a single 
safe descendant suffices to decide that a node is safe.

The algorithm now runs in four phases.

1. Run DFS to find a back edge. Then we know that both endpoints are 
   safe. Pick one, say v.

2. Run DFS from v. We collect three pieces of additional information 
   for each node: whether it is known to be safe, what is the length 
   of the longest path to a leaf of the DFS tree, and which child lies
   on that path.

   During the 2nd phase the stack will always contain one or more safe 
   nodes, followed by zero or more unsafe nodes. (Alternating is not 
   possible, since any node that is on a path from a safe node to a 
   safe node is safe itself). Whenever a back edge is encountered, 
   we can mark all nodes on the cycle as safe, including the node on 
   top of the stack; hence, since both the bottom and the top of the 
   stack are safe, we can in fact mark the whole stack as safe. This 
   can be done simply marking the nodes on the stack from the top down 
   until we hit a node that was already marked.

3. Run DFS again to decompose the remaining trees of unsafe nodes 
   in a longest path and the rest of three, which is decomposed
   recursively. For each leaf we store the length of the path that 
   ends there in a list: this is how many designs we could keep 
   afloat by adding a boat to this leaf, after having added boats
   to all longer paths in the tree.
   
4. Sort the path lengths and add up the path lengths of the k longest
   paths: this is how many designs we can save.
*/

