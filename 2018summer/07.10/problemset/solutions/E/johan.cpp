// Solution to Excellent Engineers
// Author: Johan van Rooij

// Time complexity: O(n log(n))
// Memory: O(n)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: Sort on first component, then n O(log(n)) inserts in a 2D pareto set.



#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;


class ParetoSet2D
{
public:
	
	bool addPoint( int x1, int x2 ) // returns whether the point can be added, false means that it is dominated by the current pareto set.
	{
		// set is leeg: toevoegen!
		if ( mcm2dParetoSet.empty() )
		{
			mcm2dParetoSet.insert( std::make_pair( x1, x2 ) );
			return true;
		}

		// lookup in current pareto set en test of reeds gedomineerd
		auto it = mcm2dParetoSet.upper_bound( x1 );		
		const bool undominated = ( it == mcm2dParetoSet.begin() || x2 < std::prev( it )->second );
		if ( !undominated )
			return false;

		// verwijder nieuw gedomineerde partial solutions
		auto itBeginErase = it;
		auto itEndErase = it;
		while (  itEndErase != mcm2dParetoSet.end() )
		{
			const std::pair< int, int >& current = *itEndErase;
			if ( x2 > current.second )
				break;
			++itEndErase;
		}
		mcm2dParetoSet.erase( itBeginErase, itEndErase );

		// insert new partial solution
		mcm2dParetoSet.insert( itEndErase, std::make_pair( x1, x2 ) );
		return true;
	}

private:
	// variables
	map< int, int > mcm2dParetoSet;
};

void solve()
{
	// read input
	int nrIndians;
	cin >> nrIndians;

	std::vector< std::tuple<int,int,int> > cvIndians;
	cvIndians.reserve( nrIndians );
	int x1, x2, x3;
	for	( int i = 0; i < nrIndians; ++i )
	{
		cin >> x1 >> x2 >> x3;
		cvIndians.push_back( std::make_tuple( x1, x2, x3 ) );
	}

	// compute pareto optimal points
	int nrInterestingIndians = 0;

	// 1. sort on x3
	sort( cvIndians.begin(), cvIndians.end(), []( const std::tuple<int,int,int>& tuple1, const std::tuple<int,int,int>& tuple2 ){ return std::get<2>( tuple1 ) < std::get<2>( tuple2 ); } );

	// 2. try to insert in 2d pareto front.
	ParetoSet2D paretoSet;
	for ( int i = 0; i < nrIndians; ++i )
	{
		const std::tuple<int,int,int>& curent = cvIndians[ i ]; 
		bool canInsert = paretoSet.addPoint( std::get<0>( curent ), std::get<1>( curent ) );
		if ( canInsert )
			++nrInterestingIndians;
	}

	cout << nrInterestingIndians << "\n";
}

int main()
{
	int runs; 
	cin >> runs;
	for ( int i = 0; i < runs; ++i )
		solve();
}
