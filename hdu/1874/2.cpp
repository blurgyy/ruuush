#include<bits/stdc++.h>
using namespace std;
const int maxn = 210;
const int maxm = 1010;
const int INF = 0x3f3f3f3f;

int n, m, s, t;
int d[maxn];
vector<pair<int, int> > E[maxn];

void add_edge(int u, int v, int c){
    E[u].push_back(make_pair(v, c));
    E[v].push_back(make_pair(u, c));
}

void init(){
    memset(d, 0x3f, sizeof(d));
    for(int i = 0; i < maxn; ++ i)E[i].clear();
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        int a, b, x;
        while(m--){
            scanf("%d%d%d", &a, &b, &x);
            add_edge(a, b, x);
        }
        scanf("%d%d", &s, &t);
        priority_queue<pair<int, int> > que;
        d[s] = 0;
        que.push(make_pair(-d[s], s));
        while(que.size()){
            int now = que.top().second;
            que.pop();
            for(int i = 0; i < E[now].size(); ++ i){
                int u = E[now][i].first;
                if(d[u] > d[now] + E[now][i].second){
                    d[u] = d[now] + E[now][i].second;
                    que.push(make_pair(-d[u], u));
                }
            }
        }
        printf("%d\n", d[t] == INF ? -1 : d[t]);
    }
    return 0;
}