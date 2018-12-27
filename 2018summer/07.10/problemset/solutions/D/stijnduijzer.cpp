/*
Solution by Stijn Duijzer.

// @EXPECTED_RESULTS@: CORRECT

Running time: O(n)
Memory usage: O(n)
*/
#include <iostream>
#include <vector>
using namespace std;

struct Node
{
	void create(int id_) {id = id_; for(int j=0;j<4;j++) {cin>>e[j]; e[j]--; q[j]=false;}}
	
	int id;
	int e[4];
	bool q[4];
	
	int find(int from) 
  {
    for(int j=0;j<4;j++) 
      if(e[j]==from) 
        return j;
    cout << "error in find: " << id << " " << from << endl;
    return -1;
  }
	
}; vector<Node> nodes;

int n, g;

int main()
{
	int runs; cin >> runs;
	for(int run = 1; run <= runs; run++)
	{
		cin >> n >> g; g--; nodes.clear();
		for(int i = 0; i < n; i++) { nodes.push_back(Node()); nodes[i].create(i); }
		
		int posts = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < 4; j++)
				if( !nodes[i].q[j] ) 
        {
          int nxt_i = i, nxt_j = j;
          bool found_g = false;
          while ( true )
          {
            int cur_i = nxt_i, cur_j = nxt_j;

            found_g = found_g || (cur_i == g);          
          	int k = (cur_j+2)%4;
          	if ( nodes[cur_i].q[cur_j] && nodes[cur_i].q[k] ) break;
          	nodes[cur_i].q[cur_j] = true;
            nodes[cur_i].q[k] = true;
          	
            nxt_i = nodes[cur_i].e[k];
            nxt_j = nodes[nxt_i].find(cur_i);          	
          }

          if ( !found_g ) posts++;
        }

		cout << posts << endl;
	}

	return 0;
}
	
	
	
