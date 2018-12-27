/*
solution for components by stijn duijzer

// @EXPECTED_RESULTS@: CORRECT

time complexity: O(n + d log d)
space complexity: O(n + d)
*/
#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int N = 100000+3;

struct Component 
{
	void reset(int id_) { id = id_; q.clear(); s.clear(); failed = false;}
	
	// if this comp fails, comp q[i] fails after s[i] seconds
	int id;
	vector< int > q;	
	vector< int > s;

	bool failed;
} comps[N];

struct Event
{
	Event(int t, int c) {time = t; comp = c;}
	
	// at time, comp will fail (if it has not failed already)
	int time;
	int comp;
	
	bool operator< (const Event& b) const
	{
		if ( time != b.time ) return time < b.time;
		return comp < b.comp;	
	}
};



int main()
{
	int runs; cin >> runs;
	
	for(int run = 1; run <= runs; run++)
	{
		int n, d, c; cin >> n >> d >> c;
		for(int i = 1; i <= n; i++) {comps[i].reset(i);}
		
		for(int i = 1; i <= d; i++)
		{
			int a, b, s; cin >> a >> b >> s;
			
			comps[b].q.push_back(a);
			comps[b].s.push_back(s);			
		}
		
		set<Event> H;
		int t = 0;
		
		H.insert( Event(t, c) );
		while ( !H.empty() )
		{
			c = H.begin()->comp;
			int new_t = H.begin()->time; 
			H.erase( H.begin() );
			
			if ( comps[c].failed )
			{
				continue;		
			}
			
			t = new_t;
			comps[c].failed = true;		
			
			for ( int i = 0; i < comps[c].q.size(); i++ )
			{
				int c2 = comps[c].q[i];
				if ( !comps[c2].failed )
				{
					H.insert( Event(t+comps[c].s[i], c2) );
				}
			}
		}
		
		int counter = 0;
		for(int i = 1; i <= n; i++) if (comps[i].failed) counter++;
		
		cout << counter << " " << t << endl;
	}
	
	return 0;	
}
