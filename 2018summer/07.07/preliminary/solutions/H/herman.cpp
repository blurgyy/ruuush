// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
using std::min;
using std::max;
const int MAXNR = 200000;
const int MAXPOINTS = 1 << 30;

void solve()
{
  int nrCompetitors;
  int nrSelected;
  int nrFavourites;  
  int nrStickers;    

  int favsPoints[MAXNR];
  int stickerPoints[MAXNR];

  cin >> nrCompetitors >> nrSelected >> nrFavourites;
  for (int i = 0; i < nrFavourites; ++i) cin >> favsPoints[i];
  int nrOthers = nrCompetitors - nrFavourites;      
  int* othersPoints = favsPoints + nrFavourites;  
  for (int i = 0; i < nrOthers; ++i) cin >> othersPoints[i];
  cin >> nrStickers;
  for (int i = 0; i < nrStickers; ++i) cin >> stickerPoints[i];

  sort(favsPoints, favsPoints + nrFavourites);
  sort(othersPoints, othersPoints + nrOthers);
  sort(stickerPoints, stickerPoints + nrStickers);
  
  // calculate boundaries
  int atLeast = max(0, nrSelected - nrOthers);
  int lessThan = min(nrFavourites, nrSelected) + 1;
  while (lessThan - atLeast > 1)
  {
    int toTry = (lessThan + atLeast) / 2;
    
    // take the best favourites in decreasing order and give them the best stickers in increasing order
    // this maximizes their minimum sum, since resolving inversions w.r.t this order can only raise the minimum sum
    int minSum = MAXPOINTS;
    for (int f = nrFavourites - 1, s = nrStickers - toTry; s < nrStickers; --f, ++s)
    {
      if (s >= 0) minSum = min(minSum, favsPoints[f] + stickerPoints[s]);
      else        minSum = min(minSum, favsPoints[f]);
    }

    // check if the competitors with most points are a threat
    bool success = true;
    if (nrOthers > nrSelected - toTry) 
      success = (othersPoints[nrOthers - (nrSelected - toTry) - 1] <= minSum);

    // if there are more stickers than favourites + spots in the selection for non-favourites
    // take the worst others in increasing order and give them the stickers in decreasing order; 
    // this minimizes their maximum sum; check if this is a threat
    for (int o = 0, s = nrStickers - (nrFavourites + nrSelected - toTry) - 1; success && s >= 0 && o < nrOthers; ++o, --s)
      success = (othersPoints[o] + stickerPoints[s] <= minSum);
      
    if (success)
      atLeast = toTry;
    else
      lessThan = toTry;
  }  
  cout << atLeast << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

