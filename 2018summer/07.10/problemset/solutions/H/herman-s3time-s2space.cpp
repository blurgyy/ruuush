// @EXPECTED_RESULTS@: CORRECT

/**********************************************************************
**  This code implements a solution to the petrol problem in         **
**  O(m s log n + s^4) time (proven) or                              **
**  O(m s log n + s^3) time (suspected in practice) and              **
**  O(s^2) space                                                     **
**  For explanation of the algorithm see end of file                 **
**********************************************************************/

//#define DEBUGGING
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
#include <math.h>
#include <algorithm>
using std::sort;
using std::min;
using std::swap;
#include <queue>
using std::priority_queue;

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
struct Path
{
  Cost* cheapestApproach;
  int weight;
  Cost cost;
  int otherEnd;
  bool operator<(const Path& p) const { return (weight < p.weight); }
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
  stations[nrStations].node = destination; stations[nrStations].price = 0;
  int destinationStation = nrStations;
    
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
  Cost cheapestApproach[(maxStations+1)*(maxStations+1)+1];    
  Cost* costPointer = &cheapestApproach[0];
  Path inPaths[maxStations+1][maxStations], outPaths[maxStations+1][maxStations];
  int nrInPaths[maxStations+1], nrOutPaths[maxStations+1];
  for (int i = 0; i <= nrStations; ++i) { nrInPaths[i] = 0; nrOutPaths[i] = 0; }

  for (int source = 0; source < nrStations; ++source)    // all stations except the sentinel at the destination
    for (int target = 0; target <= nrStations; ++target) 
    {
      int targetNode = stations[target].node;
      if (enterFrom[source][targetNode] == -1) continue;
      #ifdef DEBUGGING
      cout << "source=" << source << " (node " << stations[source].node << ") target="<< target << " (node " << targetNode << ")" << endl;
      #endif
      int priceIncrease = stations[target].price - stations[source].price;
      *costPointer = maxCost + 1;
      inPaths[target][nrInPaths[target]].cheapestApproach = costPointer;
      inPaths[target][nrInPaths[target]].weight = (
        priceIncrease <= 0 ? tankSize : fuelConsumption[source][targetNode]
      );
      inPaths[target][nrInPaths[target]].cost = (
        priceIncrease < 0 ?
        stations[source].price * fuelConsumption[source][targetNode] :
        stations[target].price * fuelConsumption[source][targetNode] - priceIncrease * tankSize
      );
      inPaths[target][nrInPaths[target]].otherEnd = stations[source].node;
      outPaths[source][nrOutPaths[source]].cheapestApproach = costPointer;
      outPaths[source][nrOutPaths[source]].weight = (
        priceIncrease > 0 ? tankSize : fuelConsumption[source][targetNode]
      );
      outPaths[source][nrOutPaths[source]].cost = inPaths[target][nrInPaths[target]].cost;
      outPaths[source][nrOutPaths[source]].otherEnd = targetNode;
      ++costPointer;
      ++nrInPaths[target];
      ++nrOutPaths[source];
    }
   
  // sort paths by weight
  for (int i = 0; i < nrStations; ++i)
  {
    sort(&inPaths[i][0], &inPaths[i][nrInPaths[i]]);
    sort(&outPaths[i][0], &outPaths[i][nrOutPaths[i]]);
  }
  // sentinel at destination
  *costPointer = maxCost + 1;
  outPaths[destinationStation][0].cheapestApproach = costPointer++;
  outPaths[destinationStation][0].weight = tankSize;
  outPaths[destinationStation][0].cost = 0;
  ++nrOutPaths[nrStations];

  #ifdef DEBUGGING
  for (int i = 0; i <= nrStations; ++i)
  {
    cout << "Station " << i << " (Node" << stations[i].node << "):" << endl;
    cout << "In:" << endl;
    for (int j = 0; j < nrInPaths[i]; ++j)
      cout << inPaths[i][j].otherEnd << ' ' << inPaths[i][j].weight << ' ' << inPaths[i][j].cost << ' ' << *(inPaths[i][j].cheapestApproach) << endl;
    cout << "Out:" << endl;
    for (int j = 0; j < nrOutPaths[i]; ++j)
      cout << outPaths[i][j].otherEnd << ' ' << outPaths[i][j].weight << ' ' << outPaths[i][j].cost << ' ' << *(outPaths[i][j].cheapestApproach) << endl;
    cout << "---" << endl;
  }
  #endif
  
  REPORT("Computing chepeast path along petrol stations...")
  bool improving = true;
  for (int i = 0; i < nrOutPaths[0]; ++i) *(outPaths[0][i].cheapestApproach) = 0;
  while (improving)
  {
    improving = false;
    for (int i = 0; i <= nrStations; ++i)
    {
      if (nrInPaths[i] == 0) continue;
      Cost bestApproachOnThisAndHeavierEdges[maxStations+1];
      bestApproachOnThisAndHeavierEdges[nrInPaths[i]] = maxCost + 1;
      for (int j = nrInPaths[i] - 1; j >= 0; --j)
      {
        bestApproachOnThisAndHeavierEdges[j] = bestApproachOnThisAndHeavierEdges[j+1];
        if (*(inPaths[i][j].cheapestApproach) <= maxCost)
          bestApproachOnThisAndHeavierEdges[j] = min(
            bestApproachOnThisAndHeavierEdges[j],
            *(inPaths[i][j].cheapestApproach) + inPaths[i][j].cost
          );
      }
      int minAllowedInPath = nrInPaths[i];
      for (int j = 0; j < nrOutPaths[i]; ++j)
      {
        if (inPaths[i][nrInPaths[i]-1].weight + outPaths[i][j].weight <= tankSize) continue;
        while (minAllowedInPath > 0 && inPaths[i][minAllowedInPath-1].weight + outPaths[i][j].weight > tankSize) 
          --minAllowedInPath;
        if (bestApproachOnThisAndHeavierEdges[minAllowedInPath] >= *(outPaths[i][j].cheapestApproach)) continue;
        *(outPaths[i][j].cheapestApproach) = bestApproachOnThisAndHeavierEdges[minAllowedInPath];
        improving = true;
      }
      
      #ifdef DEBUGGING     
      for (int ii = 0; ii <= nrStations; ++ii)
      {
        cout << "Station " << ii << " (Node" << stations[ii].node << "):" << endl;
        cout << "In:" << endl;
        for (int j = 0; j < nrInPaths[ii]; ++j)
          cout << inPaths[ii][j].otherEnd << ' ' << inPaths[ii][j].weight << ' ' << inPaths[ii][j].cost << ' ' << *(inPaths[ii][j].cheapestApproach) << endl;
        cout << "Out:" << endl;
        for (int j = 0; j < nrOutPaths[ii]; ++j)
          cout << outPaths[ii][j].otherEnd << ' ' << outPaths[ii][j].weight << ' ' << outPaths[ii][j].cost << ' ' << *(outPaths[ii][j].cheapestApproach) << endl;
        cout << "---" << endl;
      }
      #endif
    }      
  }

  REPORT("And here is the result...")
  cout << *(outPaths[destinationStation][0].cheapestApproach) << endl;
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

To be able to model the problem as a relatively simple least-cost path
problem, it would be convenient to give each edge a weight that 
corresponds to its cost. However, the input only gives us the amount 
of fuel needed to traverse an edge, and the cost depends on where we 
get that fuel from. We can deal with this as follows. First build a
graph G on the petrol stations, which has a directed edge (s,t) for 
each pair of petrol stations s and t that are within a full tank's 
reach from each other. Now consider how much fuel we have to buy in s 
in an optimal solution when p(s) >= p(t): it is the amount of fuel 
needed to traverse (s,t), minus the amount of fuel that is in the tank 
when we arrive at s. So, effectively, the cost of the trip up to s is the 
amount of money we spent on petrol, minus the amount of fuel left in 
the tank times the petrol price at s. Note how taking the value of the 
petrol in the tank into account does not change the total cost of a 
trip from c to d, since we start at c with an empty tank, and at d the 
petrol price is zero. This leads to the following definition of edge 
costs. Let fuel(s,t) be the amount of fuel (divided by the size of
the tank) that is needed to traverse (s,t). 

If p(s) >= p(t), then cost(s,t) = p(s) * fuel(s,t).
If p(s) <  p(t), then cost(s,t) = p(s) - p(t) (1 - fuel(s,t)).

Note that costs for traveling from s to t may differ from the costs
for travelling from t to s. Note also how in the case of p(s) < p(t), 
the first term models the cost of filling up an empty tank, while the 
second term models the value of the fuel that will be left in the tank 
when we arrive at t.

However, there is a catch: in an *non-optimal* schedule it is not 
necessarily true that we fill up completely at s when p(s) < p(t), and 
arrive with an empty tank at t when p(s) >= p(t). Consider a schedule 
with stops at, successively, stations x, y, z, where p(x) < p(y) and 
p(y) >= p(z). The core of our argument above was that in an *optimal* 
schedule, if we stop at petrol stations with such prices, z must be 
too far from x to be reachable directly from x on a full tank. 
However, in a *non-optimal* schedule, z could be within reach of x, 
and filling up at x and arriving with an empty tank at z must mean 
that fuel disappears on the way. Where does it go? With the edge costs 
as defined above, we have modelled the option to take in a negative 
amount of petrol at y, that is, we fill up with cheap petrol at x, and 
make money by selling surplus petrol at y for the higher local price. 
We may even get negative cost cycles in the graph, that is, we may be 
able to minimize the cost of our trip indefinitely by never driving to 
the destination, making a living out of the petrol trade instead.

We can solve this problem by adapting our least-cost path computation
in such a way that we do not allow stopping at expensive petrol 
stations if all we would do there is *selling* petrol. More precisely, 
after driving from x to y with a full tank (that is, p(x) < p(y)), we 
are only allowed to continue on an edge (y,z) to arrive with an empty
tank (that is, p(y) >= p(z)) if we could not have reached z directly 
from x, that is, fuel(x,y) + fuel(y,z) > 1. We can implement this by 
giving each directed edge (s,t) weights w_s(s,t) and w_t(s,t):

If p(s) >= p(t), w_s(s,t) = fuel(s,t) and w_t(s,t) = 1
If p(s) < p(t),  w_s(s,t) = 1 and w_t(s,t) = fuel(s,t)

Now, when reaching y from x, we are allowed to continue to z if 
and only if w_y(x,y) + w_y(y,z) > 1. 

To find the optimal schedule, we will now compute shortest paths on 
the graph G' that has a node for every edge of (s,t) of the petrol 
station graph G (with a sentinel edge of weight 1 leading out from the 
destination) and a link between each pair of nodes (x,y) and (y,z) 
such that w_y(x,y) + w_y(y,z). Running BF, we compute the cost of the
cheapest path to the tail of each edge; the minimum cost of reaching 
the sentinel will constitute the final answer to our query. 

If k is the number of petrol stations, then G' has O(k^2) nodes and 
O(k^3) links, and therefore Bellman-Ford runs in O(k^5) time. However, 
we can do better. The minimum cost of reaching the tail of (y,z) is 
the minimum of the cost of reaching the head of (x,y) over all x such 
that w_y(x,y) >= 1 - w_y(y,z). Now let the incoming edges of y be 
sorted in order of decreasing weight, and let the outgoing edges of y 
be sorted in order of increasing weight. Thus, as we process the 
outgoing edges of y in order, we take a non-decreasing prefix of the 
list of incoming edges into account. This enables us to relax all 
links between the edges around a vertex y in O(k) time, and thus we 
can relax all links in G' in O(k^2) time. 

The total running time for a road network with n nodes, m edges, and k
petrol stations is now:
- O(k m log n) for computing G;
- O(k^2 log k) for sorting the incoming and outgoing edges around each
  vertex;
- O(k^4) for running Bellman-Ford in O(k^2) rounds of O(k^2) time.
In total: O(k m log n + k^4).

Intuitively, one might expect that a least-cost schedule includes a
stop to buy petrol at the same petrol station at most twice. This 
would reduce the number of rounds of Bellman-Ford to O(k), and thus, 
the total running time to O(k m log n + k^3). However, there are 
actually situations in which the cheapest schedule requires buying
petrol at the same station three times (third input in testdata.in), 
and between the first and the third visit to this petrol station, the 
truck "wastes" more than twice the amount of petrol that fits in a 
full tank. It is unclear to me whether it is possible to construct 
networks and tasks that require even more stops at the same petrol 
station, and omega(k) stops in total.
**********************************************************************/
