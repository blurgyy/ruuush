#include <bits/stdc++.h>
using namespace std;
const int maxn = 50010;

int n, q, a, b, k;
int ans;
vector<int> E[maxn];
int val[maxn];

bool dfs(int now = a, int last = 0, int mark = k){
	if(mark == k){
		ans ^= val[now];
		mark = 0;
	}
	if(now == b){
		printf("%d\n", ans);
		return true;
	}
	int len = E[now].size();
	for(int i = len-1; i >= 0; -- i){
		if(E[now][i] == last)continue;
		if(dfs(E[now][i], now, mark + 1))
			return true;
	}
	if(!mark){
		ans ^= val[now];
	}
	return false;
}

int main(){
	while(~scanf("%d%d", &n, &q)){
		for(int i = 0; i < n-1; ++ i){
			scanf("%d%d", &a, &b);
			E[a].push_back(b);
			E[b].push_back(a);
		}
		for(int i = 1; i <= n; ++ i)
			random_shuffle(E[i].begin(), E[i].end());
		for(int i = 1; i <= n; ++ i)
			scanf("%d", val + i);
		while(q--){
			ans = 0;
			scanf("%d%d%d", &a, &b, &k);
			dfs();
		}
		for(int i = 1; i <= n; ++ i)
			E[i].clear();
	}
	return 0;
}