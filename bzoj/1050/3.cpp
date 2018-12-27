#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 5010;

struct edge{
    int u, v;
    int cost;
}E[maxn];
int n, m, s, t;
int fa[510];
pii ans;

bool comp(edge a, edge b){
    return a.cost < b.cost;
}

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y){
    int t1 = find(x), t2 = find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

int gcd(int a, int b){
    return b == 1 ? a : gcd(b, a % b);
}

void init(){
    ans = make_pair(30010, 1);
    for(int i = 1; i <= n; ++ i)
        fa[i] = i;
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        for(int i = 0; i < m; ++ i){
            scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].cost);
            unite(E[i].u, E[i].v);
        }
        scanf("%d%d", &s, &t);
        if(find(s) != find(t)){
            printf("IMPOSSIBLE\n");
            continue;
        }
        sort(E, E + m, comp);
        for(int i = 0; i < m; ++ i){
            for(int j = 1; j <= n; ++ j)
                fa[j] = j;
            int bot = E[i].cost, top;
            for(int j = i; j < m; ++ j){
                int u = E[j].u, v = E[j].v;
                if(find(u) == find(v))continue;
                unite(u, v);
                top = E[j].cost;
                if(find(s) == find(t)){
                    if(top * ans.second < bot * ans.first){
                        ans.first = top;
                        ans.second = bot;
                    }
                    break;
                }
            }
        }
        int g = __gcd(ans.first, ans.second);
        ans.first /= g;
        ans.second /= g;
        printf("%d", ans.first);
        if(ans.second != 1)
            printf("/%d", ans.second);
        printf("\n");
    }
    return 0;
}