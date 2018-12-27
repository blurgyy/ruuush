#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 300010;

int n, x, y, adj1, adj3;
vector<int> E[maxn];
int cnt[maxn], Prev[maxn];

void add_edge(int u, int v){
    E[u].push_back(v);
    E[v].push_back(u);
}

void init(){
    for(int i = 1; i <= n; ++ i)E[i].clear();
}

int dfs(int now, int prev = -1){
    Prev[now] = prev;
    if(now == y){
        adj3 = prev;
        int tmp = prev;
        if(tmp == x)
            adj1 = y;
        else {
            while(Prev[tmp] != x){
                tmp = Prev[tmp];
            }
            adj1 = tmp;
        }
    }
    int ret = 1;
    for(int i = 0; i < E[now].size(); ++ i){
        int nxt = E[now][i];
        if(nxt == prev)continue;
        ret += dfs(nxt, now);
    }
    cnt[now] = ret;
    return ret;
}

int main(){
    while(~scanf("%d%d%d", &n, &x, &y)){
        init();
        int u, v;
        for(int i = 1; i < n; ++ i){
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        memset(cnt, 0, sizeof(cnt));
        dfs(x);
        ll ans = 0;
        for(int i = 1; i <= n; ++ i){
            if(i == x)
                ans += cnt[i] - 1;
            else 
                ans += 1LL * cnt[i] * (n - cnt[i]);
        }
        dfs(x, adj1);
        int tmp = cnt[x];
        dfs(y, adj3);
        ans -= 1LL * tmp * cnt[y];
        printf("%I64d\n", ans);
    }
    return 0;
}

/*

3 1 3
1 2
1 3

*/