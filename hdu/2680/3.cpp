#include<bits/stdc++.h>
using namespace std;
const int maxn = 20010;
const int INF = 0x3f3f3f3f;

int n, m, s, w, in;
int ans, d[maxn];
int E[1010][1010];

void add_edge(int a, int b, int c){
    E[b][a] = min(E[b][a], c);
}

void init(){
    memset(d, 0x3f, sizeof(d));
    memset(E, 0x3f, sizeof(E));
    ans = INF;
}

int main(){
    freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    while(~scanf("%d%d%d", &n, &m, &s)){
        init();
        int u, v, c;
        while(m--){
            scanf("%d%d%d", &u, &v, &c);
            add_edge(u, v, c);
        }
        d[s] = 0;
        priority_queue<pair<int, int> > que;
        que.push(make_pair(-d[s], s));
        while(que.size()){
            int now = que.top().second;
            que.pop();
            for(int i = 1; i <= n; ++ i){
                if(E[now][i] == INF)continue;
                if(d[i] > d[now] + E[now][i]){
                    d[i] = d[now] + E[now][i];
                    que.push(make_pair(-d[i], i));
                }
            }
        }
        scanf("%d", &w);
        while(w--){
            scanf("%d", &in);
            ans = min(ans, d[in]);
        }
        printf("%d\n", ans == INF ? -1 : ans);
    }
    return 0;
}