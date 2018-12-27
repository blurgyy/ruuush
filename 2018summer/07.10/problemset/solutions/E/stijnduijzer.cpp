/*
Solution by Stijn Duijzer.

// @EXPECTED_RESULTS@: CORRECT

Running time: O(n*log(n))
Memory usage: O(n)
*/

#include <iostream>
#include <set>
using namespace std;

struct Engineer
{
	Engineer(int i) {cin>>r[0]>>r[1]>>r[2];}
	int r[3];
};

typedef std::set<Engineer,bool(*)(const Engineer&,const Engineer&)> Set;
typedef Set::iterator It;

bool E3Compare(const Engineer& a, const Engineer& b) {return a.r[0] < b.r[0];}
bool E2Compare(const Engineer& a, const Engineer& b) {return a.r[1] < b.r[1];}

int main()
{
	int runs; cin >> runs;
	
	for(int run = 1; run <= runs; run++)
	{
		int n; cin >> n;	
		Set e3(E3Compare), e2(E2Compare);
		
		for(int i = 0; i < n; i++) e3.insert( Engineer(i) );
		
		int indians = 0;
		for(It it3 = e3.begin(); it3 != e3.end(); it3++)
		{
			It it2 = e2.lower_bound(*it3); 
			bool dominated = true;
			if ( it2 == e2.begin() ) {dominated = false; }
			else {it2--; if ( it3->r[2] < it2->r[2] ) dominated = false; it2++;}			
			if ( dominated ) continue;
					 
			It a,b;
			for(a=b=it2; b!=e2.end() && it3->r[2] <= b->r[2]; b++ ) {}
			e2.erase( a, b );
			e2.insert( *it3 );
			indians++;	
		}
		cout << indians << endl;
	}	

	return 0;	
}
