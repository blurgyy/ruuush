#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, m;
vector<int> E[maxn];
bool vis[maxn];

void init(){
    for(int i = 0; i < maxn; ++ i) E[i].clear();
    memset(vis, false, sizeof(vis));
}

void add(int u, int v){
    E[u].push_back(v);
    E[v].push_back(u);
}

void dfs(int now = 1){
    vis[now] = true;
    printf("%d ", now);
    for(int i = 0; i < E[now].size(); ++ i){
        int nxt = E[now][i];
        if(vis[nxt]) continue;
        dfs(nxt);
    }
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        for(int i = 0, u, v; i < m; ++ i){
            scanf("%d%d", &u, &v);
            add(u, v);
        }
        for(int i = 1; i <= n; ++ i){
            sort(E[i].begin(), E[i].end());
        }
        dfs();
        printf("\n");
    }
    return 0;
}