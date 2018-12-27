// Solution to Excellent Engineers
// Author: Johan van Rooij

// Time complexity: O(n^2)
// Memory: O(n)

// @EXPECTED_RESULTS@: TIMELIMIT

// Solution method: Iterative inserts in pareto set that each take O(n) time.


#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;


class ParetoSet
{
public:
	ParetoSet()
	{
		mcvParetoSet.reserve( 100000 );
	}

	bool dominates( const tuple<int,int,int>& p1, const tuple<int,int,int>& p2 ) // tests whether p1 dominates p2
	{
		return get< 0 >( p1 ) < get< 0 >( p2 )
			&& get< 1 >( p1 ) < get< 1 >( p2 )
			&& get< 2 >( p1 ) < get< 2 >( p2 );
	}

	void addPoint( const tuple<int,int,int>& pNew )
	{
		bool dominated = any_of( mcvParetoSet.begin(), mcvParetoSet.end(), [=]( const tuple<int,int,int>& pSet ){ return dominates( pSet, pNew ); } );
		if ( !dominated )
		{
			mcvParetoSet.erase( 
				remove_if( mcvParetoSet.begin(), mcvParetoSet.end(), [=]( const tuple<int,int,int>& pSet ){ return dominates( pNew, pSet ); } ),
				mcvParetoSet.end() );
			mcvParetoSet.push_back( pNew );
		}
	}

	int size() const	{ return mcvParetoSet.size(); }

private:
	// variables
	vector< tuple<int,int,int> > mcvParetoSet;
};

void solve()
{
	// read input
	int nrIndians;
	cin >> nrIndians;

	ParetoSet paretoSet;

	int x1, x2, x3;
	for	( int i = 0; i < nrIndians; ++i )
	{
		cin >> x1 >> x2 >> x3;
		paretoSet.addPoint( std::make_tuple( x1, x2, x3 ) );
	}

	cout << paretoSet.size() << "\n";
}

int main()
{
	int runs; 
	cin >> runs;
	for ( int i = 0; i < runs; ++i )
		solve();
}
