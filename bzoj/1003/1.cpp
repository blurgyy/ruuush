#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 110;
const int maxm = 30;
const int inf = 0x3f3f3f3f;
// const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m, K, e;
int d, P, a, b;
ll dist[maxm];
ll dp[maxn];
bool flag[maxm];
vector<int> disabled[maxn];
vector<pii> E[maxn];

struct Node{
    int to;
    int w;
    int ne;
};

Node node[maxn<<2];
int head[maxn<<2];
int top;

void add_edge(int from, int to, int w)
{
    node[top].to = to;
    node[top].w = w;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
// for(int i = head[u]; i != -1; i = node[i].ne){
//     int nxt = node[i].to;
// }
}

ll calc(int x, int y){
    memset(flag, false, sizeof(flag));
    for(int i = 1; i <= m; ++ i){
        dist[i] = inf;
    }
    for(int i = x; i <= y; ++ i){
        for(int j = 0; j < disabled[i].size(); ++ j){
            flag[disabled[i][j]] = true;
        }
    }
    for(int i = 1; i <= m; ++ i){
        E[i].clear();
        if(flag[i]) continue;
        for(int j = head[i]; j != -1; j = node[j].ne){
            int nxt = node[j].to;
            if(flag[nxt]) continue;
            E[i].push_back(make_pair(nxt, node[j].w));
            // printf("%d and %d connected\n", i, nxt);
        }
    }
    dist[1] = 0;
    priority_queue<pii> que;
    que.push(make_pair(-dist[1], 1));
    while(que.size()){
        int now = que.top().second;
        que.pop();
        for(int i = 0; i < E[now].size(); ++ i){
            int nxt = E[now][i].first;
            int w = E[now][i].second;
            if(dist[nxt] > dist[now] + w){
                // printf("%d > %d + %d\n", dist[nxt], dist[now], w);
                dist[nxt] = dist[now] + w;
                que.push(make_pair(-dist[nxt], nxt));
            }
        }
    }
    // printf("calc(%d, %d) = %lld\n", x, y, dist[m]);
    return dist[m] * (y - x + 1);
}

void ini(){
    top = 0;
    memset(head, -1, sizeof(head));
}

void init(){
    for(int i = 1; i <= n; ++ i){
        disabled[i].clear();
    }   
    memset(dp, 0x3f, sizeof(dp));
    ini();
}

int main(){
    while(~scanf("%d%d%d%d", &n, &m, &K, &e)){
        init();
        for(int i = 0, u, v, w; i < e; ++ i){
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
        scanf("%d", &d);
        while(d --){
            scanf("%d%d%d", &P, &a, &b);
            for(int i = a; i <= b; ++ i){
                disabled[i].push_back(P);
            }
        }
        for(int i = 1; i <= n; ++ i){
            dp[i] = calc(1, i);
            for(int j = 1; j < i; ++ j){
                dp[i] = min(dp[i], dp[j] + K + calc(j+1, i));
            }
            // printf("dp[%d] = %lld\n", i, dp[i]);
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}
