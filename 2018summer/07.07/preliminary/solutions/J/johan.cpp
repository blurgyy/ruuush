// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <string>
#include <tuple>
#include <vector>


using namespace std;

// returns 1 if found in this direction, 0 if not
int findWord( vector< vector<char> >& grid, vector< vector<bool> >& found, const string& word, int startx, int starty, int dx, int dy )
{
	int x = startx;
	int y = starty;
	for ( int i = 0; i < word.length(); ++i )
	{
		if ( x < 0 || x >= grid.front().size() || y < 0 || y >= grid.size() )
			return 0;
		if ( grid[ y ][ x ] != word [ i ] )
			return 0;
		x += dx;
		y += dy;
	}

	// found!!
	x = startx;
	y = starty;
	for ( int i = 0; i < word.length(); ++i )
	{
		found[ y ][ x ] = true;
		x += dx;
		y += dy;
	}
	return 1;
}

bool isPalindrome( const string& word )
{
	for ( int i = 0; i < word.length() / 2; ++i )
	{
		if ( word[ i ] != word[ word.length() - i - 1 ] )
			return false;
	}
	return true;
}

void solve()
{
	//
	// Read input
	//
	int n;
	int h;
	int w;
	cin >> n >> h >> w;

	vector< vector<char> > grid( h, vector<char>( w, ' ') );
	for ( int y = 0; y < h; y++ )
		for ( int x = 0; x < w; x++ )
			cin >> grid[y][x];
	
	vector< string > words;
	words.reserve( n );
	string newWord;
	getline( cin, newWord );
	for ( int i = 0; i < n; ++i )
	{
		getline( cin, newWord );
		words.push_back( newWord );
	}

	//
	// helper data structure
	//
	vector< vector<bool> > found( h, vector<bool>( w, false ) );
	std::pair<int,int> searchDirections[] = { make_pair( 0, 1 ), make_pair( 1, 1 ), make_pair( 1, 0 ), make_pair( 1, -1 ),
											  make_pair( 0, -1 ), make_pair( -1, -1 ), make_pair( -1, 0 ), make_pair( -1, 1 ) };		

	//
	//
	//
	bool ambiguous = false;
	for ( auto itWord = words.begin(); itWord != words.end(); ++itWord )
	{
		const string& word = *itWord;

		bool palindrome = isPalindrome( word );
		int findCount = 0;

		for ( int x = 0; x < w; ++x )
		{
			for ( int y = 0; y < h; ++y )
			{
				if ( grid[y][x] == word[0] )
				{
					if ( word.length() == 1 )
					{
						findCount += findWord( grid, found, word, x, y, searchDirections[ 0 ].first, searchDirections[ 0 ].second );
					}
					else
					{
						for ( int direction = 0; direction < 8; ++direction )
							findCount += findWord( grid, found, word, x, y, searchDirections[ direction ].first, searchDirections[ direction ].second );
					}
				}
			}
		}

		if ( !( findCount == 1 || ( palindrome && findCount == 2 ) ) )
		{
			if ( findCount == 0 )
			{
				cout << "no solution\n";
				return;
			}
			ambiguous = true;
		}
	}

	if ( ambiguous )
	{
		cout << "ambiguous\n";
		return;
	}

	bool solutionIsEmpty = true;
	for ( int y = 0; y < h; ++y )
	{
		for ( int x = 0; x < w; ++x )
		{
			if ( !found[y][x] )
			{
				cout << grid[y][x];
				solutionIsEmpty = false;
			}
		}
	}

	if ( solutionIsEmpty )
		cout << "empty solution";
	cout << "\n";
}

int main()
{
	int runs; 
	cin >> runs;
	for ( int i = 0; i < runs; ++i )
		solve();
}
