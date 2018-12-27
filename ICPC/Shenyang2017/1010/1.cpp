#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 10010;

int n, u, v, p;
int fa[maxn];
struct node
{
	int failed;
	set<int> rec;
}server[maxn];

int Find(int x){
	return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

void unite(int x, int y){
	int f1 = Find(x), f2 = Find(y);
	if(f1 == f2)return;
	fa[x] = y;
}

bool Same(int x, int y){
	return Find(x) == Find(y);
}

void init(){
	for(int i = 0; i < maxn; ++ i){
		fa[i] = i;
		server[i].failed = 0;
		server[i].rec.clear();
	}
}

void add(int p1, int p2){
	server[p1].rec.insert(p2);
	server[p2].rec.insert(p1);
	
}

int main(){
	while(!scanf("%d", &n)){
		init();
		for(int i = 0; i < n; ++ i){
			scanf("%d%d", &u, &v);
			unite(u, v);
		}
		scanf("%d", &p);
		for(int i = 0; i < p; ++ i){
			scanf("%d%d", &u, &v);

		}
	}
}