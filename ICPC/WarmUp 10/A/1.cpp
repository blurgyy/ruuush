#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, m, x, y;
int dis[maxn], path[maxn], p;
bool vis[maxn], dfsed[maxn];
vector<int> E[maxn];

void dfs(int now, int d = 0){
    dis[now] = min(dis[now], d);
    vis[now] = true;
    dfsed[now] = true;
    int len = E[now].size();
    for(int i = 0; i < len; ++ i){
        if(!vis[E[now][i]])
            dfs(E[now][i], d+1);
    }
    vis[now] = false;
}

int get_d(int now){
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dfs(now);
    int id, ma = -1;
    for(int i = 0; i < maxn; ++ i){
        if(dis[i] == INF)continue;
        if(dis[i] > ma){
            ma = dis[i];
            id = i;
        }
    }
    memset(dis, 0x3f, sizeof(dis));
    //memset(vis, false, sizeof(vis));
    dfs(id);
    ma = -1;
    for(int i = 0; i < maxn; ++ i){
        if(dis[i] == INF)continue;
        if(dis[i] > ma){
            ma = dis[i];
            id = i;
        }
    }
    return (ma+1)>>1;
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        for(int i = 0; i < maxn; ++ i)E[i].clear();
        memset(dfsed, false, sizeof(dfsed));
        p = 0;
        while(m--){
            scanf("%d%d", &x, &y);
            E[x].push_back(y);
            E[y].push_back(x);
        }
        for(int i = 0; i < maxn; ++ i){
            if(!dfsed[i])
                path[p++] = get_d(i);
        }
        sort(path, path + p);
        int ans = 0;
        if(p > 1)ans = 1 + path[p-1] + path[p-2];
        else ans = path[p-1];
        printf("%d\n", ans);
    }
    return 0;
}
