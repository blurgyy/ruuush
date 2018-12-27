// @EXPECTED_RESULTS@: CORRECT
// O(n^2 log^2 n) time and O(n log n) space

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <algorithm>
using std::sort;
using std::min;
using std::max;
using std::swap;
#include <set>
using std::set;
#include <vector>
using std::vector;

const int maxN = 1004;    // add some to allow for sentinel vertices
const int maxCuts = 1025; // must be power of two + 1, larger than maxN
const int minY = 0;
const int maxY = 100000;

struct Segment
{
  int first, second, location;
  bool operator<(const Segment& s) const
  {
    return (location < s.location);
  }
};
struct Segments
{
  Segment array[2*maxN];
  int size;
  Segments(): size(0) {};
  Segment* begin() { return &array[0]; }
  Segment* end() { return &array[size]; }
  void insert(int f, int s, int l) 
  {
    array[size].first = f;
    array[size].second = s;
    array[size].location = l;
    ++size;
  }
};

struct SegmentTree
{
  int cutsArray[maxCuts]; int nrCuts;
  vector<int> spanningSegments[2*maxCuts]; 
  vector<int> pokingSegments[maxCuts]; 
  void print() // for debugging only
  {
    for (int i = 0; i < nrCuts; ++i) cout << cutsArray[i] << ' '; cout << endl;
    cout << "Spanners:" << endl;
    for (int i = 0; i < 2*nrCuts; ++i)
    {
      cout << i/2 << ((i&1)? " leaf" : " cut") << ':';
      for (int j = 0; j < spanningSegments[i].size(); ++j) cout << ' ' << spanningSegments[i][j];
      cout << endl;
    }
    cout << "Pokers:" << endl;
    for (int i = 0; i < nrCuts; ++i)
    {
      cout << i << ':';
      for (int j = 0; j < pokingSegments[i].size(); ++j) cout << ' ' << pokingSegments[i][j];
      cout << endl;
    }
    cout << endl;
  }
  void insertSegment(Segment& s, int leftCut, int rightCut)
  {
    int midCut = (leftCut + rightCut)/2;
    if (rightCut - leftCut == 1) 
    {
      spanningSegments[2*midCut+1].push_back(s.location);
      return;
    }
    pokingSegments[midCut].push_back(s.location);
    if (s.first <= cutsArray[leftCut] && s.second >= cutsArray[rightCut])
    {
      spanningSegments[2*midCut].push_back(s.location);
      return;
    }
    if (s.first < cutsArray[midCut]) insertSegment(s, leftCut, midCut);
    if (s.second > cutsArray[midCut]) insertSegment(s, midCut, rightCut);
  }
  SegmentTree(Segments& segments)
  {
    // get balanced tree on segment end points
    set<int> cuts;
    for (Segment* s = segments.begin(); s != segments.end(); ++s)
    {
      cuts.insert(s->first); cuts.insert(s->second);
    }
    nrCuts = 0;
    for (set<int>::iterator c = cuts.begin(); c != cuts.end(); ++c)
    {
      cutsArray[nrCuts] = *c;
      ++nrCuts;
    }
    // add some to get a perfectly balanced tree
    while ((nrCuts-1) & (nrCuts-2)) // as long as it is not a power of two plus one
      cutsArray[nrCuts] = cutsArray[nrCuts++ -1];
      
    // insert segments
    sort(segments.begin(), segments.end());
    for (Segment* s = segments.begin(); s != segments.end(); ++s)
      insertSegment(*s, 0, nrCuts-1);
    return;
  }
  int find(vector<int>& array, int cut)
  {
    // returns the number in array[0..size-1] that is on or just below cut 
    if (array.empty()) return -(maxY+1);
    if (array[0] > cut) return -(maxY+1);
    int lowerBound = 0, upperBound = array.size();
    while (upperBound - lowerBound > 1)
    {
      int mid = (lowerBound + upperBound)/2;
      if (array[mid] > cut) upperBound = mid;
      else lowerBound = mid;
    }
    return array[lowerBound];
  }
  int findInSlab(int left, int right, int cut, int leftCut, int rightCut)
  {
    int midCut = (leftCut + rightCut)/2;
    if (rightCut == leftCut + 1) return find(spanningSegments[2*midCut+1], cut);
    int lowerBound = find(spanningSegments[2*midCut], cut);
    if (left <= cutsArray[leftCut] && right >= cutsArray[rightCut])
      return max(lowerBound, find(pokingSegments[midCut], cut));
    if (left < cutsArray[midCut])
      lowerBound = max(lowerBound, findInSlab(left, min(right,cutsArray[midCut]), cut, leftCut, midCut));
    if (right > cutsArray[midCut]) 
      lowerBound = max(lowerBound, findInSlab(max(left,cutsArray[midCut]), right, cut, midCut, rightCut));
    return lowerBound;  
  }
  int findInSlab(int left, int right, int cut)
  {
    return findInSlab(left, right, cut, 0, nrCuts-1);  
  }
};

void solve()
{
  Segments leftSegments;   leftSegments.insert(-1, maxY+1, -1); leftSegments.insert(-1, maxY+1, maxY+1);
  Segments rightSegments;  rightSegments.insert(-1, maxY+1, -maxY-1); rightSegments.insert(-1, maxY+1, 1);
  Segments bottomSegments; bottomSegments.insert(-1, maxY+1, -1); bottomSegments.insert(-1, maxY+1, maxY+1);
  Segments topSegments;    topSegments.insert(-1, maxY+1, -maxY-1); topSegments.insert(-1, maxY+1, 1);
  Segments* lowxSegments = &leftSegments;
  Segments* lowySegments = &bottomSegments;
  Segments* highxSegments = &rightSegments;
  Segments* highySegments = &topSegments;
  int nrVertices; int x[maxN+1], y[maxN+1];
  cin >> nrVertices;
  for (int i = 0; i < nrVertices; ++i) cin >> x[i] >> y[i];
  x[nrVertices] = x[0]; y[nrVertices] = y[0];
  for (int i = 1; i <= nrVertices; ++i)
  {
    if (x[i] == x[i-1])
    {
      if (y[i] < y[i-1]) // right edge
        rightSegments.insert(y[i], y[i-1], -x[i]);
      else // left edge
        leftSegments.insert(y[i-1], y[i], x[i]);
    }
    else
    {
      if (x[i] < x[i-1]) // bottom edge
        bottomSegments.insert(x[i], x[i-1], y[i]);
      else // top edge
        topSegments.insert(x[i-1], x[i], -y[i]);
    }
  }
  SegmentTree leftTree(leftSegments); 
  SegmentTree rightTree(rightSegments); 
  SegmentTree bottomTree(bottomSegments);
  SegmentTree topTree(topSegments); 
  SegmentTree* lowxTree = &leftTree;
  SegmentTree* lowyTree = &bottomTree;
  SegmentTree* highxTree = &rightTree;
  SegmentTree* highyTree = &topTree;
  int bestSize = 0;
  for (int h = 0; h < 2; ++h)    
  {      
    for (int i = 1; i < lowxSegments->size-1; ++i)
      for (int j = 1; j < highxSegments->size-1; ++j)
      {
        int lowx = lowxSegments->array[i].location;
        int highx = -highxSegments->array[j].location;
        if (highx <= lowx + bestSize) continue;
        int lowy = max(lowxSegments->array[i].first, highxSegments->array[j].first);
        int highy = min(lowxSegments->array[i].second, highxSegments->array[j].second);
        if (lowy > highy) swap(lowy, highy);
        int lowerBound = lowyTree->findInSlab(lowx, highx, highy);
        int upperBound = -highyTree->findInSlab(lowx, highx, -lowy);
        if (upperBound <= lowerBound + bestSize) continue;
        highy = upperBound; lowy = lowerBound;
        lowerBound = lowxTree->findInSlab(lowy, highy, highx);
        upperBound = -highxTree->findInSlab(lowy, highy, -lowx);
        if (upperBound <= lowerBound + bestSize) continue;
        lowx = lowerBound; highx = upperBound;
        bestSize = max(bestSize, min(highx - lowx, highy - lowy));
      }
    swap(lowxSegments,lowySegments); swap(lowxTree,lowyTree);
    swap(highxSegments,highySegments); swap(highxTree,highyTree);
  }  
  cout << bestSize << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}
