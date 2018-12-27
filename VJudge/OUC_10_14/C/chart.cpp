//For fuck's sake

#include<bits/stdc++.h>
using namespace std;
const int maxn = 5000;

int fa[maxn];
int a, b, c;
vector<int> path;
set<vector<int> > rec;

int Find(int x){
	return fa[x] == x ? x : Find(fa[x]);
}

void Unite(int a, int b){
	int t1 = Find(a), t2 = Find(b);
	if(t1 == t2)continue;
	fa[t1] = t2;
}

bool Same(int a, int b){
	return Find(a) == Find(b);
}

void init(){
	rec.clear();
	path.clear();
	for(int i = 0; i < maxn; ++ i)
		fa[i] = i;
}

int main(){
	while(~scanf("%d%d%d", &a, &b, &c)){
		init();
		int sum = a + b + c;
		for(int i = 1; i <= sum; ++ i){
			if(i == 1 || i == a+1 || i == b+1)continue;
			if(i <= a)
				Unite(1, i);
			else if(i <= b)
				Unite(a+1, i);
			else Unite(b+1, i);
		}-
	}
	return 0;
}