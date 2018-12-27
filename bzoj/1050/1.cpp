#include <bits/stdc++.h>
using namespace std;
const int maxn = 5010;
const int inf = 0x3f3f3f3f;

int n, m, s, t;
int fa[510];
vector<pair<int, int> > E[maxn];
struct node{
    node(int _top = inf, int _bot = 1){
        init(_top, _bot);
    }
    void init(int _top = inf, int _bot = 1){
        int gcd = __gcd(_top, _bot);
        top = _top / gcd;
        bot = _bot / gcd;
        val = (double)top / (double)bot;
    }
    bool operator< (node b){
        return val < b.val;
    }
    int top, bot;
    double val;
}ans;

int find(int x){
    return x == fa[x] ? x : find(fa[x]);
}

bool same(int x, int y){
    return find(x) == find(y);
}

void unite(int x, int y){
    int t1 = find(x), t2 = find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

void add_edge(int u, int v, int dist){
    E[u].push_back(make_pair(v, dist));
    E[v].push_back(make_pair(u, dist));
    unite(u, v);
}

void init(){
    for(int i = 0; i < 510; ++ i){
        E[i].clear();
        fa[i] = i;
    }
    ans.init();
}

void dfs(int now = s, int prev = -1, int mx = -1, int mn = inf){
    if(now == t){
        node a(mx, mn);
        if(a < ans){
            ans = a;
        }
        return;
    }
    for(int i = 0; i < E[now].size(); ++ i){
        int nxt = E[now][i].first, dis = E[now][i].second;
        if(nxt == prev)continue;
        int t1 = mx, t2 = mn;
        mx = max(mx, dis);
        mn = min(mn, dis);
        printf("%d to %d, %d/%d\n", now, nxt, mx, mn);
        dfs(nxt, now, mx, mn);
        mx = t1, mn = t2;
    }
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        while(m --){
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            add_edge(u, v, d);
        }
        scanf("%d%d", &s, &t);
        if(!same(s, t)){
            printf("IMPOSSIBLE\n");
            continue;
        }
        dfs();
        if(ans.bot == 1){
            printf("%d\n", ans.top);
        }
        else{
            printf("%d/%d\n", ans.top, ans.bot);
        }
    }
    return 0;
}

/**

3 3

1 2 10

1 2 5

2 3 8

1 3

*/