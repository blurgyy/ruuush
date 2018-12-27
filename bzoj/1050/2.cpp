#include <bits/stdc++.h>
using namespace std;
const int maxn = 5010;

struct Edge{
    int s, e, v;
}E[maxn<<1];
int n, m, s, t, pt;
int fa[maxn];

bool cmp(Edge a, Edge b){
    return a.v < b.v;
}

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

void init(){
    pt = 0;
    memset(E, 0, sizeof(E));
    for(int i = 0; i < maxn; ++ i)
        fa[i] = i;
}

void add_edge(int u, int v, int c){
    E[pt].s = u;
    E[pt].e = v;
    E[pt++].v = c;
    /*
    E[pt].s = v;
    E[pt].e = u;
    E[pt++].v = c;
    */
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        for(int i = 0; i < m; ++ i){
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            add_edge(u, v, c);
        }
        scanf("%d%d", &s, &t);
        sort(E, E + pt, cmp);
        double minx = 1e15;
        pair<int, int> ans = make_pair(-1, -1);
        for(int i = 0; i < pt; ++ i){
            int bot = E[i].v, top;
            for(int j = i; j < pt; ++ j){
                int u = E[j].s, v = E[j].e;
                if(same(u, v))continue;
                unite(u, v);
                top = E[j].v;
                if(same(s, t)){
                    double now = (double)top / (double)bot;
                    if(now < minx){
                        ans = make_pair(top, bot);
                        minx = now;
                    }
                    break;
                }
            }
            for(int i = 1; i <= n; ++ i)
                fa[i] = i;
        }
        if(ans.first == -1){
            printf("IMPOSSIBLE\n");
            continue;
        }
        int g = __gcd(ans.first, ans.second);
        ans.first /= g;
        ans.second /= g;
        if(ans.second == 1){
            printf("%d\n", ans.first);
        }
        else {
            printf("%d/%d\n", ans.first, ans.second);
        }
    }
    return 0;
}