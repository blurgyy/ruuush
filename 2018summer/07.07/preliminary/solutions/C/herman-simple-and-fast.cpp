// @EXPECTED_RESULTS@: CORRECT
// O(n^2 log n log w) time and O(n^2) space

/**********************************************************************
Approach:

This implementation builds a data structure on the grid defined by the
horizontal and the vertical lines through the input points. All cells
that are outside the input polygon are marked. This is done as follows:
we sort the horizontal segments of the input polygon by increasing 
y-coordinate; when we hit a segment oriented to the left (bounding the 
polygon from below), we mark everything down from that segment until 
we hit cells already marked; when we hit a segment oriented to the 
right (bounding the polygon from above), we mark the cells just above 
that segment. The marking phase is completed by processing a sentinel
segment oriented to the left that lies above the entire polygon.

Next we turn the grid into a data structure that gives us for each 
cell, the first marked cell to the right and the first marked cell 
above. This is done by simply passing this information down from the
upper right corner to the lower left corner of the grid (as in 
dynamic programming). So far, the algorithm takes only O(n^2) time.

With the data structure we can determine in O(log n) time if an empty 
square with lower left corner in a specific cell and with a specific 
size exists as follows: by binary search in the sorted lists of x- and
y-coordinates, we can calculate which four cells should contain the 
four corners of the square, and then four queries into the data 
structure inform us whether the cells between those corners (more 
precisely, the cells along the edges of the square) are free. If yes,
then the square is valid, nothing inside the square can be outside the
polygon if the corners lie inside the polygon and the polygon boundary 
does not intersect the edges of the square.

We now iterate over all cells of the grid while maintaining the 
size of the smallest square that has been found to exist. For each 
cell we do binary search between that lower bound and a trivial upper
bound to find the largest possible square that fits. We test O(n^2)
candidates for lower left corner cells, and for each we do O(log w)
queries (where w is the coordinate range) in O(log n) time. Thus the
algorithm takes O(n^2 log n log w) time.
*********************************************************************/

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::setw;
#include <algorithm>
using std::min;
using std::max;
#include <set>
using std::set;
#include <vector>
using std::vector;

const int maxN = 1000;    
const int maxDiffCoordPerDimension = maxN/2;
const int maxGridSize = (maxDiffCoordPerDimension+1)*(maxDiffCoordPerDimension+1);
const int minCoord = 0;
const int maxCoord = 100000;
const int maxSize = maxCoord - minCoord;

struct Grid
{
  int* storage;
  Grid(): storage(new int[maxGridSize]) {};
  int& operator()(const int row, const int col) { return storage[(row-1)*(maxDiffCoordPerDimension+1)+(col-1)]; }
};

struct Segment
{
  int first, second, elevation;
  Segment(int f, int s, int e): first(f), second(s), elevation(e) {};
  bool operator<(const Segment& s) const
  {
    return (elevation < s.elevation);
  }
};

int getIndex(const vector<int>& array, const int x)
{
  // may assume that x lies strictly between the lowest and highest number in the array
  // must err on the high side if x is not in the array
  int lowerBound = 0, upperBound = array.size()-1;
  while (upperBound - lowerBound > 1)
  {
    int cut = (lowerBound + upperBound) / 2;
    if (x <= array[cut]) upperBound = cut; 
    else lowerBound = cut;
  }
  return upperBound;
}

void solve()
{
  set<int> xCoordSet;
  set<int> yCoordSet;
  
  // read all vertices
  int nrVertices; int x[maxN+1], y[maxN+1];
  cin >> nrVertices;
  for (int i = 0; i < nrVertices; ++i) 
  { 
    cin >> x[i] >> y[i];
    xCoordSet.insert(x[i]);
    yCoordSet.insert(y[i]);
  }
  x[nrVertices] = x[0]; y[nrVertices] = y[0];
 
  // make arrays of x- and y-coordinates without doubles
  vector<int> xCoords; xCoords.push_back(minCoord-maxSize-1); // sentinel
  vector<int> yCoords; yCoords.push_back(minCoord-maxSize-1); // sentinel
  for (set<int>::iterator i = xCoordSet.begin(); i != xCoordSet.end(); ++i) xCoords.push_back(*i);
  for (set<int>::iterator i = yCoordSet.begin(); i != yCoordSet.end(); ++i) yCoords.push_back(*i);
  xCoords.push_back(maxCoord+maxSize+1); // sentinel
  yCoords.push_back(maxCoord+maxSize+1); // sentinel

  // created list of horizontal edges sorted by elevation
  vector<Segment> horizontalEdges;
  for (int i = 0; i < nrVertices; ++i)
    if (y[i] == y[i+1]) 
      horizontalEdges.push_back(Segment(x[i], x[i+1], y[i]));
  horizontalEdges.push_back(Segment(xCoords.back(), xCoords.front(), yCoords.back())); // to mark everything above the polygon as occupied
  sort(horizontalEdges.begin(), horizontalEdges.end());
    
  // initialize occupancy grid
  int nrCols = xCoords.size()-1;
  int nrRows = yCoords.size()-1;
  Grid firstOccupiedAbove;
  Grid firstOccupiedRight;
  for (int row = 1; row <= nrRows; ++row)
  {
    firstOccupiedAbove(row, 1) = row; firstOccupiedRight(row, 1) = 1;
    for (int col = 2; col < nrCols; ++col) 
    {
      firstOccupiedAbove(row, col) = 1; firstOccupiedRight(row, col) = nrCols;
    }
    firstOccupiedAbove(row, nrCols) = row; firstOccupiedRight(row, nrCols) = nrCols;
  } 
  
  // paint the polygon's complement by letting grid cells refer to themselves
  for (vector<Segment>::iterator i = horizontalEdges.begin(); i != horizontalEdges.end(); ++i)
  {
    int firstIndex = getIndex(xCoords, i->first);
    int secondIndex = getIndex(xCoords, i->second);
    int yIndex = getIndex(yCoords, i->elevation);
    // if going to the right, mark cells just above
    for (int col = firstIndex + 1; col <= secondIndex; ++col)
    {
      firstOccupiedAbove(yIndex+1, col) = yIndex+1;
      firstOccupiedRight(yIndex+1, col) = col;
    }
    // if going to the left, mark off everything below until hitting an edge
    for (int col = secondIndex + 1; col <= firstIndex; ++col)
      for (int row = yIndex; firstOccupiedAbove(row, col) != row; --row)
      {
        firstOccupiedAbove(row, col) = row;
        firstOccupiedRight(row, col) = col;
      }
  }
  // fix the top row
  for (int col = 1; col <= nrCols; ++col) 
  {
    firstOccupiedAbove(nrRows, col) = nrRows; firstOccupiedRight(nrRows, col) = col;
  }
  
  // pass down occupancy information to the right and to the bottom
  for (int row = 2; row < nrRows; ++row)
    for (int col = nrCols-1; col > 1; --col)
      if (firstOccupiedRight(row, col) != col)
        firstOccupiedRight(row, col) = firstOccupiedRight(row, col+1);
  for (int col = 2; col < nrCols; ++col)
    for (int row = nrRows-1; row > 1; --row)
      if (firstOccupiedAbove(row, col) != row)
        firstOccupiedAbove(row, col) = firstOccupiedAbove(row+1, col);

  // search
  int maxSizeKnownToWork = 0;
  for (int bottomRow = 2; bottomRow < nrRows; ++bottomRow)
    for (int leftCol = 2; leftCol < nrCols; ++leftCol)
    {
      if (firstOccupiedRight(bottomRow, leftCol) == leftCol) continue;
      int minSizeKnownToFail = min(
        xCoords[xCoords.size()-2] + 1 - xCoords[leftCol-1], 
        yCoords[yCoords.size()-2] + 1 - yCoords[bottomRow-1]
      );
      while (minSizeKnownToFail - maxSizeKnownToWork > 1)
      {
        int trySize = (maxSizeKnownToWork + minSizeKnownToFail) / 2;
        int topRow = getIndex(yCoords, yCoords[bottomRow-1]+trySize);
        int rightCol = getIndex(xCoords, xCoords[leftCol-1]+trySize);
        if (
          firstOccupiedRight(bottomRow, leftCol) > rightCol &&
          firstOccupiedAbove(bottomRow, rightCol) > topRow &&
          firstOccupiedAbove(bottomRow, leftCol) > topRow &&
          firstOccupiedRight(topRow, leftCol) > rightCol
        )
        {
          // cout << bottomRow << ' ' << leftCol << ' ' << trySize << endl;
          maxSizeKnownToWork = trySize;
        }
        else
          minSizeKnownToFail = trySize;
      }
    }

  cout << maxSizeKnownToWork << endl;      
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}
