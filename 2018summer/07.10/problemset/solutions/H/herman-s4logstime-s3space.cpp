// @EXPECTED_RESULTS@: CORRECT

/**********************************************************************
**  This code implements a solution to the petrol problem in         **
**  O(m s log n + s^4 log s) time and                                **
**  O(s^3) space                                                     **
**  For explanation of the algorithm see end of file                 **
**********************************************************************/

//#define DEBUGGING
#ifdef DEBUGGING
#define REPORT(activity) cerr << activity << endl;
#define SPLIT(id) (id >> 14) << ',' << ((id >> 7) & ((1 << 7) - 1)) << ',' << (id & ((1 << 7) - 1))
#else
#define REPORT(activity)
#endif

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <math.h>
#include <algorithm>
using std::sort;
using std::min;
using std::swap;
#include <queue>
using std::priority_queue;
#include <bitset>
using std::bitset;

const int maxNodes = 1000;
const int maxEdges = 10000;
const int maxDirectedEdges = 2*maxEdges;
const int maxStations = 120;
const int maxPetrol = 100000;
const int maxPrice = 100;
typedef long long int Cost;
const Cost maxCost = maxStations * maxPetrol * maxPrice;

void refuse(const char* message)
{
  cerr << message << endl;
  exit(1);
}

struct Edge
{
  int tail, head, fuelConsumption;
  bool operator<(const Edge& e) const { return (tail < e.tail); }
};

struct Station
{
  int node, price;
};

struct NodeDistance
{
  int node;
  Cost distance;
  NodeDistance(int n, Cost d): node(n), distance(d) {};
  bool operator<(const NodeDistance& p) const { return (distance > p.distance); }
};

struct Heap
{
  Cost* cost;
  int* heapToId;
  int* idToHeap;
  bitset< (1 << 21) > undetermined;
  int size;
  Heap():
    cost(new Cost[1 << 21]),
    heapToId(new int[1 << 21 + 1]),
    idToHeap(new int[1 << 21]),
    size(0)
  {};
  void print()
  {
    #ifdef DEBUGGING
    cout << "Heap ";
    for (int i = 1; i <= size; ++i)
    {
      int id = heapToId[i];
      if (idToHeap[id] != i || !undetermined[id]) 
      {
        cerr << "inconsistent!" << endl;
        exit(1);
      }
      cout << '(' << SPLIT(id) << ':' << cost[id] << ')';
    }
    cout << endl;
    #endif
  }
  void insert(int id)
  {
    REPORT("inserting " << SPLIT(id))
    cost[id] = maxCost + 1;
    ++size;
    heapToId[size] = id;
    idToHeap[id] = size;
    undetermined.set(id);
    print();
  }
  void decreaseCost(int id, int c)
  {
    REPORT("decreasing cost of " << SPLIT(id) << " to at most " << c)
    if (!undetermined[id]) return;
    if (cost[id] <= c) return;
    cost[id] = c;
    int heapIndex = idToHeap[id];
    while (heapIndex > 1 && c < cost[heapToId[heapIndex >> 1]])
    {
      heapToId[heapIndex] = heapToId[heapIndex >> 1]; 
      idToHeap[heapToId[heapIndex]] = heapIndex;
      heapIndex >>= 1;
      heapToId[heapIndex] = id;
      idToHeap[id] = heapIndex;
    }
    print();
  }  
  void extractMin(int& id, int& c)
  {
    if (size == 0) 
    {
      cerr << "Extracting from empty heap" << endl;
      exit(1);
    }
    id = heapToId[1];
    c = cost[id];
    REPORT("Extracting " << SPLIT(id) << " with cost " << c)
    undetermined.reset(id);
    int idToInsert = heapToId[size];
    --size;
    int heapIndex = 1; 
    for (int childIndex = 2; childIndex <= size; heapIndex = childIndex, childIndex = heapIndex << 1)
    {
      if (childIndex < size && cost[heapToId[childIndex+1]] < cost[heapToId[childIndex]])
        ++childIndex;
      if (cost[idToInsert] < cost[heapToId[childIndex]]) break;
      heapToId[heapIndex] = heapToId[childIndex];
      idToHeap[heapToId[heapIndex]] = heapIndex;
    }
    heapToId[heapIndex] = idToInsert;
    idToHeap[idToInsert] = heapIndex;
    print();
  }
};

void solve()
{
  REPORT("Reading basic input parameters...")
  int nrNodes, nrEdges, nrDirectedEdges, nrStations, tankSize;
  cin >> nrNodes;
  if (nrNodes < 2) refuse ("Number of nodes too small");
  if (nrNodes > maxNodes) refuse ("Number of nodes too large");
  cin >> nrEdges; nrDirectedEdges = 2*nrEdges;
  if (nrEdges < 1) refuse ("Number of edges too small");
  if (nrEdges > maxEdges) refuse ("number of edges too large");
  cin >> nrStations;
  if (nrStations < 1) refuse ("Number of petrol stations too small");
  if (nrStations > maxStations) refuse ("Number of petrol stations too large");
  cin >> tankSize;
  if (tankSize < 1) refuse ("Fuel tank too small");
  if (tankSize > maxPetrol) refuse ("Fuel tank too large");

  REPORT("Reading edges...")
  Edge edges[maxDirectedEdges+1];
  for (int toRead = nrEdges, toWrite = 0; toRead > 0; --toRead)
  {
    cin >> edges[toWrite].tail >> edges[toWrite].head >> edges[toWrite].fuelConsumption;
    if (edges[toWrite].tail < 1 || edges[toWrite].tail > nrNodes) refuse ("Edge starts at node that is out of range");
    if (edges[toWrite].head < 1 || edges[toWrite].head > nrNodes) refuse ("Edge starts at node that is out of range");
    if (edges[toWrite].fuelConsumption < 1 || edges[toWrite].fuelConsumption > tankSize) refuse ("Fuel consumption on edge is out of range");
    ++toWrite; 
    edges[toWrite] = edges[toWrite-1]; swap(edges[toWrite].head, edges[toWrite].tail);
    ++toWrite;
  }
  edges[nrDirectedEdges].tail = nrNodes + 1; // sentinel

  REPORT("Constructing adjacency lists...")
  Edge* adjacencyList[nrNodes+1];
  sort(&edges[0], &edges[nrDirectedEdges]);
  adjacencyList[1] = &edges[0];
  for (int i = 2; i <= nrNodes; ++i)
  {
    adjacencyList[i] = adjacencyList[i-1];
    while (adjacencyList[i]->tail < i) ++adjacencyList[i];
  }  

  REPORT("Reading stations...")
  Station stations[maxStations+1];
  for (int i = 0; i < nrStations; ++i)
  {
    cin >> stations[i].node >> stations[i].price;
    if (stations[i].node < 1 || stations[i].node > nrNodes) refuse ("Fuel station at node that is out of range");
    if (stations[i].price < 1 || stations[i].price > maxPrice) refuse ("Price at fuel station is out of range");
  }

  // make company the first station, remove any station at the destination, and replace by a sentinel with free petrol
  int company, destination;
  cin >> company;
  if (company < 1 || company > nrNodes) refuse ("Company at node that is out of range");
  cin >> destination;
  if (destination < 1 || destination > nrNodes) refuse ("Company at node that is out of range");
  if (company == destination) refuse ("Company and destination are the same location");
  for (int i = 1; i < nrStations; ++i)
  {
    if (stations[i].node == company) swap(stations[i], stations[0]);
    if (stations[i].node == destination) swap(stations[i], stations[--nrStations]);
  }
  if (stations[0].node != company) refuse ("No petrol station at the company");
  const int companyStation = 0;
  stations[nrStations].node = destination; stations[nrStations].price = 0;
  const int destinationStation = nrStations;
    
  REPORT("Computing distances from petrol stations...")
  int fuelConsumption[maxStations+1][maxNodes+1];
  int enterFrom[maxStations+1][maxNodes+1]; // to record shortest paths tree for possible use in debugging
  priority_queue<NodeDistance> Q;
  int lastMarked[maxNodes+1]; for (int node = 1; node <= nrNodes; ++node) lastMarked[node] = -1;
  for (int source = 0; source < nrStations; ++source)
  {
    for (int node = 1; node <= nrNodes; ++node) 
    {
      fuelConsumption[source][node] = maxCost + 1;
      enterFrom[source][node] = -1;
    }
    fuelConsumption[source][stations[source].node] = 0;
    enterFrom[source][stations[source].node] = stations[source].node;
    Q.push(NodeDistance(stations[source].node, 0));
    while (!Q.empty())
    {
      int node = Q.top().node;
      Q.pop();
      if (lastMarked[node] == source) continue;
      lastMarked[node] = source;
      for (Edge* neighbour = adjacencyList[node]; neighbour->tail == node; ++neighbour)
      {
        Cost distance = fuelConsumption[source][node] + neighbour->fuelConsumption;
        if (distance >= fuelConsumption[source][neighbour->head]) continue;
        if (distance > tankSize) continue;
        fuelConsumption[source][neighbour->head] = distance;
        enterFrom[source][neighbour->head] = node;
        Q.push(NodeDistance(neighbour->head, distance));
      }    
    }
  }

  REPORT("Constructing graph on petrol stations...")
  Heap heap;
  Cost* spending = new Cost[1 << 21];
  for (int x = 0; x < nrStations; ++x) // exclude x = nrStations = destinationStation
  {
    for (int y = 0; y <= nrStations; ++y)
    {
      int yNode = stations[y].node;
      if (enterFrom[x][yNode] == -1) continue; // y cannot be reached directly from x
      for (int z = 0, segmentId = (x << 14) | (y << 7); z <= nrStations; ++z, ++segmentId)
      { 
        // segmentId's are the id's of nodes (x,y,z) in G', and are 21 bits' numbers:
        // 7 bits for x, 7 bits for y, 7 bits for z
        int zNode = stations[z].node;
        if (enterFrom[y][zNode] == -1) continue; // z cannot be reached directly from y
        spending[segmentId] = stations[y].price * fuelConsumption[x][yNode];
        if (stations[x].price >= stations[y].price) spending[segmentId] += stations[y].price * (tankSize - fuelConsumption[x][yNode]);
        if (stations[y].price >= stations[z].price) spending[segmentId] -= stations[y].price * (tankSize - fuelConsumption[y][zNode]);
        if (spending[segmentId] < 0) continue; // prevent any attempts to sell petrol
        heap.insert(segmentId);
      }
    }
  }

  REPORT("Computing least-cost path from company to destination...")
  // initialize by decreasing the key for nodes that start with (companyStation, companyStation, ...) = (0, 0, ...) to zero
  for (int z = 0; z <= nrStations; ++z) heap.decreaseCost(z, 0);
  // run Dijkstra's
  while (true)
  {
    int segmentId, cost;
    heap.extractMin(segmentId, cost);
    if (((segmentId >> 7) & ((1 << 7) - 1)) == destinationStation)
    {
      REPORT("And here is the result...")
      cout << cost << endl;
      break;
    }
    cost += spending[segmentId];
    for (int z = 0, nextSegmentId = (segmentId & ((1 << 14) - 1)) << 7; z <= nrStations; ++z, ++nextSegmentId) 
      heap.decreaseCost(nextSegmentId, cost);
  }
  
  delete [] spending;
}

int main()
{
  double bits = 0;
  bits += log2(maxStations);
  bits += log2(maxPetrol);
  bits += log2(maxPrice);
  if (ceil(bits) > 8*sizeof(Cost)-2) 
    refuse("Range of integer type to store costs is too small");
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

/**********************************************************************
For ease of notation (and implementation), we let the destination node 
d have a petrol station with free petrol, and when we reach d, we 
always fill up. Obviously, this will not affect the cost of an optimal 
solution. In this explanation the unit of fuel used will be one full 
tank.

Let a "schedule" be a route together with a plan of where to get how 
much petrol. For a given schedule, let s_1,...,s_k be the petrol 
stations where we get petrol, where s_1 is the starting node c and s_k 
is the destination node d. Let p(X) be the petrol price (that is, the 
cost of a full tank) at station X, where, by definition, p(s_k) = 0. 
Now we observe that there is an optimal schedule such that the 
following holds for any i in 1,...,k-1:

(i) If p(s_i) >= p(s_{i+1}), then we get just enough petrol at s_i to
reach s_{i+1} with an empty tank.
(ii) If p(s_i) < p(s_{i+1}), then we fill the tank completely at s_i.

Part (i) is easy. Part (ii) can be proven as follows. Let s_j be the
first petrol station after s_i such that p(s_j) <= p(s_i). The 
distance from s_i to s_j (along the chosen route) must be more than we 
can drive on one full tank, otherwise, instead of taking petrol at the 
expensive stations s_{i+1},...,s_{j-1}, we would be better off buying 
more petrol at s_i and/or s_j and skipping s_{i+1},...,s_{j-1}. Now, 
given that we cannot reach s_j on a full tank directly from s_i, any 
fuel that is left in the tank when we reach s_j must be the result of 
taking more than we need at the stations s_{i+1},...,s_{j-1}. But it 
would be cheaper to buy that surplus petrol at s_j after arriving with 
an empty tank. Hence, all petrol bought at s_i,...,s_{j-1} should be 
just enough to reach s_j (using also what was in the tank when we 
arrived at s_i), and, to the extent allowed by the capacity of the 
fuel tank, this petrol is best bought at s_i where it is cheaper than 
at s_{i+1},...,s_{j-1}. So we fill up at s_i.

Let fuel(s,t) be the amount of fuel (divided by the size of the tank) 
that is needed to drive from petrol station s to petrol station t.

The above implies that if we visit the petrol stations x, y, and z 
consecutively in this order, then we can determine the amount of money
spent on petrol in y as follows. 

* if p(x) >= p(y) and p(y) >= p(z), we spend p(y) * fuel(y,z)
  (arrive with empty tank, buy just enough petrol to reach z)

* if p(x) >= p(y) and p(y) < p(z), we spend p(y)
  (arrive with empty tank and fill up)
  
* if p(x) < p(y) and p(y) >= p(z), we spend 
  p(y) * (fuel(x,y) + fuel(y,z) - 1)
  (after filling up at x and using fuel(x,y), replenish just 
  enough to reach z)
  
* if p(x) < p(y) and p(y) < p(z), we spend p(y) * fuel(x,y)
  (replenish what was used after filling up at x)
  
However, visiting the stations x, y, z consecutively is not allowed 
if any of the following applies:

* fuel(x,y) > 1
* fuel(y,z) > 1
* p(x) < p(y) and p(y) >= p(z) and fuel(x,y) + fuel(y,z) < 1

The first two restrictions are obvious; the latter says that we are
not allowed to stop at an expensive petrol station y between two cheap
stations x and z if z is reachable directly from x. Forbidding such 
stops is crucial, because otherwise, with the formulas given above, we 
would calculate that we spend p(y) * (fuel(x,y) + fuel(y,z) - 1) < 0 
on petrol in y, that is, we would model the possibility of reducing 
the cost of our trip by filling up at x and selling surplus petrol at 
y.

To find the optimal schedule, we will now compute shortest paths on 
the graph G' that has a node for every trip of petrol stations 
(x,y,z), an edge between each pair of triples (w,x,y) and (x,y,z), and
node costs as defined above (there are no costs associated with the 
edges of G'). For each node, we compute the minimum expense for the 
trip up to (but excluding) y. Using Dijkstra's algorithm, the 
computation finishes as soon as a node (x,y,z) is reached where y = d. 
To make sure that such a node exists we simply include nodes of the
form (x,d,d) in the graph.

Note that G' has Theta(k^3) nodes and Theta(k^4) edges in the worst 
case. To prevent problems with memory for large k, a priority queue 
with a decrease-key operation is used.

The total running time for a road network with n nodes, m edges, and k
petrol stations is now:
- O(k m log n) for computing the distances between all petrol stations;
- O(k^4 log k) for running Dijkstra's algorithm on G'.

**********************************************************************/
