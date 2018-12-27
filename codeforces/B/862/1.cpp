#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 100010;

ll n, u, v;
ll odd, even;
int vis[maxn];
vector<ll> E[maxn];

void init(){
    odd = even = 0;
    memset(vis, 0, sizeof(vis));
	for(int i = 0; i < maxn; ++ i)
		E[i].clear();
}

void dfs(ll u = 1, int level = 1){
    if(!vis[u])vis[u] ++;
    //printf("%d: %d %d, u = %d\n", level, odd, even, u);
    //printf("vis[%d] = %d\n", u, vis[u]);
    if(level&1)++ odd;
    else ++ even;
    int len = E[u].size();
    for(int i = 0; i < len; ++ i){
        if(!vis[E[u][i]]){
            dfs(E[u][i], level + 1);
        }
    }
}

int main(){
	while(~scanf("%I64d", &n)){
        init();
		for(int i = 0; i < n-1; ++ i){
			scanf("%I64d%I64d", &u, &v);
			E[u].push_back(v);
			E[v].push_back(u);
		}
		dfs();
		//printf("%d %d\n", odd, even);
		printf("%I64d\n", odd * even - n + 1);
	}
	return 0;
}
