#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 300010;

vector<int> E[maxn];
int n, x, y, adj, Prev[maxn];
int cnt[maxn];

int dfs(int now, int prev = -1){
    Prev[now] = prev;
    if(now == y){
        int tmp = now;
        while(Prev[tmp] != x)
            tmp = Prev[tmp];
        adj = tmp;
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

void init(){
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i <= n; ++ i)E[i].clear();
}

int main(){
    while(~scanf("%d%d%d", &n, &x, &y)){
        init();
        int u, v;
        for(int i = 1; i < n; ++ i){
            scanf("%d%d", &u, &v);
            E[u].push_back(v);
            E[v].push_back(u);
        }
        dfs(x);
        ll ans = 1LL * n * (n - 1);
        ans -= 1LL * (n - cnt[adj]) * cnt[y];
        printf("%I64d\n", ans);
    }
    return 0;
}