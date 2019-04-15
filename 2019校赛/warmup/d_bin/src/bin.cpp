#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int maxm = 10010;

int T, n, m, w;
int fa[maxn];
struct Edge{
    int u, v, t;
    void input(){
        scanf("%d%d%d", &u, &v, &t);
    }
    bool operator< (const Edge &rhs){return t < rhs.t;}
}E[maxm];

int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
bool same(int x, int y){return find(x) == find(y);}
void unite(int x, int y){
    int t1 = find(x), t2 = find(y);
    if(t1 == t2) return;
    fa[t1] = t2;
}

void init(){
    for(int i = 1; i <= n; ++ i) fa[i] = i;
}

bool check(int ans){
    init();
    for(int i = 1; i <= ans; ++ i){
        unite(E[i].u, E[i].v);
    }
    for(int i = 1; i <= n; ++ i){
        if(!same(i, 1)) return false;
    }
    return true;
}

int solve(int left = 1, int right = m){
    if(left >= right) return right;
    int mid = left + (right - left) / 2;
    if(check(mid)) return solve(left, mid);
    return solve(mid + 1, right);
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%d%d", &n, &m, &w);
        for(int i = 1, u, v, t; i <= m; ++ i){
            E[i].input();
        }
        sort(E+1, E+1 + m);
        int ans = E[solve()].t;
        // printf("ans = %d\n", ans);
        while(w --){
            int q;
            scanf("%d", &q);
            if(q >= ans) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
