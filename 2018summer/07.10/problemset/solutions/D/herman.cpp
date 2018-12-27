// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <bitset>
using std::bitset;
#include <algorithm>
using std::swap;

const int maxN = 100000;
const int even = 0;
const int odd = 1;

struct Solver
{
  int nrVertices, goal;
  bitset<maxN+1> marked[2];
  int neighbours[maxN+1][4];
  void walk(int& vertex, int& road)
  {
    int nextVertex = neighbours[vertex][road];
    for (int j = 0; j < 4; ++j)
      if (neighbours[nextVertex][j] == vertex)
        road = (j & 1);
    if (neighbours[nextVertex][road] == vertex)
      swap (neighbours[nextVertex][road], neighbours[nextVertex][road+2]);
    vertex = nextVertex;
  }
  Solver()
  {
    cin >> nrVertices >> goal;
    for (int i = 1; i <= nrVertices; ++i)
      for (int j = 0; j < 4; ++j)
        cin >> neighbours[i][j];
    int vertex = goal; int road = even;
    while (!marked[road][vertex]) { marked[road].set(vertex); walk(vertex, road); }
    road = odd;
    while (!marked[road][vertex]) { marked[road].set(vertex); walk(vertex, road); }
    int nrSignPosts = 0;
    for (int startRoad = 0; startRoad < 2; ++startRoad)
      for (int startVertex = 1; startVertex <= nrVertices; ++startVertex)
        if (!marked[startRoad][startVertex])
        {
          ++nrSignPosts;
          int vertex = startVertex; int road = startRoad;
          while (!marked[road][vertex]) { marked[road].set(vertex); walk(vertex, road); }
        }
    cout << nrSignPosts << endl;
  }
};

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) { Solver s; }
}
