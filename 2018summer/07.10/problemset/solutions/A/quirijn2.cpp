/******************************************************************************/
/* Problem: Avoiding the Apocalypse                                           */
/* Solution: Max-Flow on time-layered graph                                   */
/* Time: O(VE^2) but faster in practice since we limit the flow to p          */
/* Author Quirijn Bouts                                                       */
// @EXPECTED_RESULTS@: CORRECT
/******************************************************************************/

#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define MAX_VERTS 101002
#define LOG2_MAX_VERTS 10
#define EACH_NEIGHBOR(K) (vector<EdgeInfo>::iterator it = Q[K].adj.begin(); it!= Q[K].adj.end(); it++)

//graph definitions

struct EdgeInfo{
	int to;
	int cap=0;
	int flow=0;
	EdgeInfo(int a, int b): to(a),cap(b),flow(0){}
};

struct Vertex{
	int parent;
	vector<EdgeInfo> adj;
};

int V, E,origV;
Vertex Q[MAX_VERTS];


//max-flow
int source,sink;

bool Search() {
	for (int i=0; i<V; i++)
		Q[i].parent = -1;
	queue<int> sr;
	sr.push(source);
	Q[source].parent = -2;
	while (!sr.empty()) {
		int k = sr.front(); sr.pop();
		for EACH_NEIGHBOR(k) {
			if (Q[it->to].parent == -1 &&
						it->flow < it->cap) {
				Q[it->to].parent = k;
				if (it->to == sink) return true;
				sr.push(it->to);
			}
		}
	}
	return false;
}

int MaxFlow() {
	auto Cap=[&](int from, int to){for EACH_NEIGHBOR(from) { if(it->to==to){return it->cap;}}return 0;};
	auto Flow=[&](int from, int to){for EACH_NEIGHBOR(from) { if(it->to==to){return it->flow;}}return 0;};
	auto IncFlow=[&](int from, int to, int inc){for EACH_NEIGHBOR(from) { if(it->to==to){it->flow+=inc;return;}}};

	while (Search()) {
		int k=sink;
		int k2 = Q[k].parent;
		int m = Cap(k2,k) - Flow(k2,k);
		while (k2!=-2) {
			m = min(m, Cap(k2,k)-Flow(k2,k));
			k=k2; k2=Q[k].parent;
		}
		k=sink;
		k2=Q[k].parent;
		while (k2!=-2) {
			IncFlow(k2,k,m);
			IncFlow(k,k2,-m);
			k=k2; k2=Q[k].parent;
		}
	}
	int sum=0;
	for (int i=0; i<V; i++) sum +=Flow(source,i);
	return sum;
}


void Code(){
	int start,people,limit,nTargets;
	vector<int> targets;
	//input
	cin >> V >> start >> people>> limit >> nTargets;
	start--; //input uses 1-based system to index vertices, we are 0-based
	origV=V;
	//reset everything which may still contain data from previous run
	for(int i=0;i<MAX_VERTS;i++){
		Q[i].adj.clear();
	}
	int tmp;
	for(int i=0;i<nTargets;i++){
		cin >> tmp;
		targets.push_back(tmp-1);
	}
	cin >> E;
	int x,y,enter,cross;
	//we construct a time-layered graph with a vertex for each location at each timestep
	for(int i=0;i<E;i++){
		cin >> x >> y >> enter >> cross;
		x--;y--; //input uses 1-based system to index vertices, we work from 0
		for(int i=0;i<limit-cross+1;i++){
			Q[V*i+x].adj.push_back(EdgeInfo(V*(i+cross)+y,enter));
			Q[V*(i+cross)+y].adj.push_back(EdgeInfo(V*i+x,0));
		}
	}
	//add source and supersink, set V to be the number of vertices in the time-layered graph
	sink=V*(limit+1);
	source=V*(limit+1)+1;
	//edge with capacity p from source to start to limit max flow and never get an invalid answer
	Q[source].adj.push_back(EdgeInfo(start,people));
	Q[start].adj.push_back(EdgeInfo(source,0));
	for(int i=0;i<nTargets;i++){
		//for all targets in the last time step, we add edge to supersink
		Q[targets[i]+V*limit].adj.push_back(EdgeInfo(sink,100000000));
		Q[sink].adj.push_back(EdgeInfo(targets[i]+V*limit,0));
	}
	//it should also be possible to wait at locations...
	for(int i=0;i<V*(limit);i++){
		Q[i].adj.push_back(EdgeInfo(i+V,1000000000));
		Q[i+V].adj.push_back(EdgeInfo(i,0));
	}
	V=V*(limit+1)+1;
	//run max-flow
	int survived=MaxFlow();
	cout << survived <<endl;
}

int main(){
	int runs;
	cin >> runs;
	while(runs--){
		Code();
	}
	return 0;
}


