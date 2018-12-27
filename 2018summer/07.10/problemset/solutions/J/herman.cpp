// @EXPECTED_RESULTS@: CORRECT
// #define DEBUGGING

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ws;
#include <bitset>
using std::bitset;
#include <sstream>
using std::string;
using std::istringstream;
#include <algorithm>
using std::swap;
using std::max;
using std::min;
#include <stack>
using std::stack;
using std::pair;
typedef pair<int,int> Location;

const int maxW = 100; 
const int maxH = 100; 
const int entranceRow = maxH-1;
const int nrRows = 2*entranceRow + 1;
const int col = 0;
const int row = 1;

struct Solver
{
  bitset<maxW+1> wall[nrRows];
  bitset<maxW+1> known[nrRows];
  int maxColReached, minRowReached, maxRowReached;
  bool noWall(const int r, const int c) const
  {
    return known[r][c] && !wall[r][c];
  }
  void fillUnreachableAreas()
  {
    bitset<maxW+1> reachable[nrRows];
    for (int r = minRowReached-1; r <= maxRowReached+1; ++r)
    {
      for (int c = 0; c <= maxColReached+1; ++c)
      {
        if (reachable[r][c]) continue;
        if (!known[r][c]) continue;
        // DFS from here
        stack<Location> DFSstack;
        DFSstack.push(Location(r,c));
        while (!DFSstack.empty())
        {
          Location here = DFSstack.top();
          DFSstack.pop();
          if (here.first < minRowReached-1 || here.first > maxRowReached+1) continue;
          if (here.second < 0 || here.second > maxColReached+1) continue;
          if (wall[here.first][here.second]) continue;
          if (reachable[here.first][here.second]) continue;
          reachable[here.first][here.second] = true;
          DFSstack.push(Location(here.first-1, here.second));
          DFSstack.push(Location(here.first, here.second+1));
          DFSstack.push(Location(here.first+1, here.second));
          DFSstack.push(Location(here.first, here.second-1));
        }
      }
    }
    for (int r = minRowReached-1; r <= maxRowReached+1; ++r)
      for (int c = 0; c <= maxColReached+1; ++c)
        if (!known[r][c] && !reachable[r][c]) 
        {
          known[r][c] = true;
          wall[r][c] = true;
        }
  }
  void drawMaze() const
  {
    bool determined = true;
    cout << maxRowReached - minRowReached + 3 << ' ' << maxColReached + 2 << endl;
    for (int r = minRowReached-1; r <= maxRowReached+1; ++r)
    {
      for (int c = 0; c <= maxColReached+1; ++c)
      {
        // #ifdef DEBUGGING
        if (known[r][c])
          cout << (wall[r][c] ? '#' : '.');
        else
        {
          cout << '?';
          if (c == 0) continue;
          if (noWall(r+1,c) || noWall(r,c+1) || noWall(r-1,c) || noWall(r,c-1))
            determined = false;
        }
        // #else
        // cout << (wall[r][c] || !known[r][c] ? '#' : '.');
        // #endif
      }
      cout << endl;
    }
    if (!determined) cout << "Maze not completely determined" << endl;
  }
  void turnLeft(int heading[2]) const
  {
    swap(heading[row], heading[col]);
    heading[row] = -heading[row];
  }
  void turnRight(int heading[2]) const
  {
    heading[row] = -heading[row];
    swap(heading[row], heading[col]);
  }
  void placeWall(const int r, const int c, const bool hasWall) 
  {
    if (known[r][c])
    {
      if (wall[r][c] != hasWall)
      {
        cout << "Inconsistent information!" << endl;
      }
      // return;
    }
    known[r].set(c);
    wall[r].set(c, hasWall);
  }
  Solver()
  {
    std::string line;
    std::getline(cin, line);
    std::istringstream iss(line);
    for (int r = 0; r < entranceRow; ++r) placeWall(r, 0, true);
    int location[2]; location[col] = 0; location[row] = entranceRow;
    maxColReached = location[col];
    maxRowReached = location[row];
    minRowReached = location[row];
    placeWall(entranceRow, 0, false);
    for (int r = entranceRow+1; r < nrRows; ++r) placeWall(r, 0, true);
    int heading[2]; heading[col] = 1; heading[row] = 0;
    char c; 
    while (iss >> c) 
    {
      #ifdef DEBUGGING
      cout << endl; drawMaze();      
      #endif
      switch(c)
      {
        case 'B': 
          placeWall(location[row]+heading[col], location[col]-heading[row], true);
          turnLeft(heading);
        case 'L': 
          placeWall(location[row]+heading[col], location[col]-heading[row], true);
          turnLeft(heading);
        case 'F': 
          placeWall(location[row]+heading[col], location[col]-heading[row], true);
          turnLeft(heading);
        case 'R':
          turnRight(heading);
          location[row] += heading[row]; location[col] += heading[col];
          #ifdef DEBUGGING
          cout << "Moving " << c << " to row " << location[row] << " column " << location[col] << endl;
          #endif
          maxColReached = max(location[col], maxColReached);
          maxRowReached = max(location[row], maxRowReached);
          minRowReached = min(location[row], minRowReached);
          placeWall(location[row], location[col], false);
          break;
        default:
          cerr << "Input error" << endl;
          exit(1);
      }
    }
    fillUnreachableAreas();
    drawMaze();
    #ifdef DEBUGGING
    cout << "-------------------------------" << endl; // for debugging only
    #endif
  }
};

int main()
{
  int nrTestCases;
  cin >> nrTestCases >> ws;
  cout << nrTestCases << endl;
  while (--nrTestCases >= 0) { Solver s; }
}
