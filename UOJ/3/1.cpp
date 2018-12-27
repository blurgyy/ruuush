#include <bits/stdc++.h>
using namespace std;
const int maxn = 50010;

struct node{
    node(int _a = 0,  int _b = 0){init(_a, _b);}
    void init(int _a = 1, int _b = 0){
        a = _a;
        b = _b;
    }
    int a, b;
};
vector<pair<int, node> > E[maxn];
int n, m, ans;
int fa[maxn];
bool vis[maxn];

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool same(int x, int y){
    return find(x) == find(y);
}

void unite(int x, int y){
    int t1 = find(x), t2 = find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

void add_edge(int x, int y, int a, int b){
    node tmp(a, b);
    E[x].push_back(make_pair(y, tmp));
    E[y].push_back(make_pair(x, tmp));
    unite(x, y);
}

void dfs(int now = 1, int aa = -1, int bb = -1){
  /*for(int i = 1; i <= n; ++ i)
        printf("%d ", vis[i]);
    printf("\n");
*/

    vis[now] = true;
    if(now == n){
        //printf("a = %d, b = %d\n", aa, bb);
        if(ans > aa + bb){
            ans = aa + bb;
        }
        vis[now] = false;
        return;
    }
    for(int i = 0; i < E[now].size(); ++ i){
        int nxt = E[now][i].first;
        if(vis[nxt])continue;
        node tmp = E[now][i].second;
        int ta = aa, tb = bb;
        aa = max(aa, tmp.a);
        bb = max(bb, tmp.b);
        //printf("%d to %d\n", now, nxt);
        dfs(nxt, aa, bb);
        aa = ta;
        bb = tb;
    }
    vis[now] = false;
}

void init(){
    ans = 0x7fffffff;
    for(int i = 0; i < maxn; ++ i)
        fa[i] = i;
    memset(vis, false, sizeof(vis));
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        while(m --){
            int x, y, a, b;
            scanf("%d%d%d%d", &x, &y, &a, &b);
            add_edge(x, y, a, b);
        }
        if(!same(1, n)){
            printf("-1\n");
            continue;
        }
        dfs();
        printf("%d\n", ans);
    }
    return 0;
}