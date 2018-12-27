// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::setw;
using std::setfill;
#include <string>
using std::string;

void solve()
{
  const int dcol[8] = {0,1,1,1,0,-1,-1,-1}; const int drow[8] = {-1,-1,0,1,1,1,0,-1};
  const int MAXH = 32; const int MAXW = 32; const int MAXN = 256;
  int n; int h; int w; char grid[MAXH+2][MAXW+2]; bool marked[MAXH+2][MAXW+2];
  cin >> n >> h >> w;
  for (int j = 0; j <= w+1; ++j) grid[0][j] = '-';
  for (int i = 1; i <= h; ++i) 
  {
    grid[i][0] = '-';
    for (int j = 1; j <= w; ++j) 
    {
      cin >> grid[i][j];
      marked[i][j] = false;
    }
    grid[i][w+1] = '-';
  }
  for (int j = 0; j <= w+1; ++j) grid[h+1][j] = '-';
  string word;
  bool nosolution = false;
  bool ambiguous = false;
  for (int k = 0; k < n; ++k) 
  {
    do getline(cin, word); while (word.size() == 0);
    if (nosolution) continue; // answer is known, still to scan the rest of the input
    int nrDirectionsToSearch = 8;
    if (word.size() == 1) 
      nrDirectionsToSearch = 1;
    else
    {
      // check if it is a palindrome
      bool palindrome = true;
      for (int i = 0; palindrome && i < word.size() / 2; ++i)
        palindrome = (word[i] == word[word.size()-1-i]);
      if (palindrome) nrDirectionsToSearch = 4;
    }
    bool found = false;
    for (int i = 1; i <= h && !(found && ambiguous); ++i)
      for (int j = 1; j <= w && !(found && ambiguous); ++j)
        for (int d = 0; d < nrDirectionsToSearch && !(found && ambiguous); ++d)
        {
          bool match = true;
          for (int c = 0, ii = i, jj = j; match && c < word.size(); ii += drow[d], jj += dcol[d], ++c)
            match = (grid[ii][jj] == word[c]);
          if (!match) continue;
          ambiguous = ambiguous || found;
          found = true;
          for (int c = 0, ii = i, jj = j; c < word.size(); ii += drow[d], jj += dcol[d], ++c)
            marked[ii][jj] = true;
        }
    // if (!found) cout << "cannot find " << word << endl;
    nosolution = nosolution || !found;
  }
  if (nosolution)
    cout << "no solution";
  else if (ambiguous)
    cout << "ambiguous";
  else 
  {
    bool empty = true;
    for (int i = 1; i <= h; ++i)
      for (int j = 1; j <= w; ++j)
        if (!marked[i][j]) 
        {
          cout << grid[i][j];
          empty = false;
        }
    if (empty) cout << "empty solution";
  }
  cout << endl;
}

int main()
{
  int nrTestCases;
  cin >> nrTestCases;
  while (--nrTestCases >= 0) solve();
}

