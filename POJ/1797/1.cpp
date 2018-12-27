//并没有读题。。。果然调不出来
//改天再看

#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 1000010;

int T, n, m;
int fa[maxn];
vector<pair<int, int> > E[maxn];

int Find(int x){
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

void Unite(int x, int y){
	int t1 = Find(x), t2 = Find(y);
	if(t1 == t2)return;
	fa[t1] = t2;
}

bool Same(int x, int y){
	return Find(x) == Find(y);
}

void init(){
	for(int i = 0; i <= n; ++ i){
		E[i].clear();
		fa[i] = i;
	}
}

void Init_Union_Find(){
	for(int i = 0; i <= n; ++ i)
		fa[i] = i;
}

void add_edge(int u, int v, int c){
	E[u].push_back(make_pair(v, c));
	E[v].push_back(make_pair(u, c));
}

bool check(int cost){
	for(int i = 1; i <= n; ++ i){
		for(int j = 0; j < E[i].size(); ++ j){
			if(E[i][j].second <= cost)Unite(i, j);
		}
	}
	if(Same(1, n))return true;
	return false;
}

int bs(int left = 0, int right = maxn){
	if(left >= right)return right;
	int mid = (left + right) >> 1;
	if(!check(mid))return bs(mid+1, right);
	return bs(left, mid);
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		init();
		int x, y, z;
		while(m--){
			scanf("%d%d%d", &x, &y, &z);
			add_edge(x, y, z);
		}
		printf("%d\n", bs());
	}
	return 0;
}