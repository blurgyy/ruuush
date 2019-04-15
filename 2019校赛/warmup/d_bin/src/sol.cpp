#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int maxm = 1000010;
const ll inf = 0x7fffffffffffffff;

int T;
int n, m, q;
// int fa[maxn], cnt[maxn];
int fa[maxn];
struct Edge{
    int u, v;
    ll w;
    bool operator< (Edge &rhs){return w < rhs.w;}
}E[maxm];

int Find(int x)
{
    int t;

    t = x;
    while(t != fa[t]){
        t = fa[t];
    }
    while(x != t){
        int q;

        q = fa[x];
        fa[x] = t;
        x = q;
    }

    return t;
}

int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
bool same(int x, int y){return Find(x) == Find(y);}
// bool same(int x, int y){return find(x) == find(y);}
void unite(int x, int y){
    // int t1 = find(x), t2 = find(y);
    int t1 = Find(x), t2 = Find(y);
    if(t1 == t2) return;
    fa[t1] = t2;
    // if(cnt[t1] > cnt[t2]) {
    //     fa[t2] = t1;
    //     cnt[t1] += cnt[t2];
    // }
    // else {
    //     fa[t1] = t2;
    //     cnt[t2] += cnt[t1];
    // }
}

bool connected(){
    for(int i = 1; i <= n; ++ i){
        if(!same(1, n)) return false;
    }
    return true;
}

void init(){
    for(int i = 1; i <= n; ++ i) fa[i] = i;
    // for(int i = 1; i <= n; ++ i) cnt[i] = 1;
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%d%d", &n, &m, &q);
        init();
        for(int i = 0, u, v, w; i < m; ++ i){
            scanf("%d%d%lld", &E[i].u, &E[i].v, &E[i].w);
        }
        sort(E, E + m);
        ll ans = -1;
        for(int i = 0; i < m; ++ i){
            int u = E[i].u, v = E[i].v;
            if(same(u, v)) continue;
            unite(u, v);
            // ans = min(ans, E[i].w);
            // ans = max(ans, E[i].w);
            ans = E[i].w;
        }
        if(!connected()) ans = inf;
        // printf("ans = %lld\n", ans);
        while(q --){
            int query;
            scanf("%d", &query);
            if(query >= ans) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
