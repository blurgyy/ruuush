//Floyd 46ms
//Dijkstra 15ms

#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;
const int INF = 0x3f3f3f3f;

int n, m;
int u, v, cost;
int s, t;
int d[maxn];
vector<pair<int, int> > E[maxn];

void add_edge(){
    E[u].push_back(make_pair(v, cost));
    E[v].push_back(make_pair(u, cost));
}

void init(){
    for(int i = 0; i < maxn; ++ i)E[i].clear();
    memset(d, 0x3f, sizeof(d));
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        while(m--){
            scanf("%d%d%d", &u, &v, &cost);
            add_edge();
        }
        scanf("%d%d", &s, &t);
        d[s] = 0;
        priority_queue<pair<int, int> > Q;
        Q.push(make_pair(-d[s], s));
        while(!Q.empty()){
            int now = Q.top().second;
            int len = E[now].size();
            Q.pop();
            for(int i = 0; i < len; ++ i){
                int u = E[now][i].first;
                if(d[u] > d[now] + E[now][i].second){
                    d[u] = d[now] + E[now][i].second;
                    Q.push(make_pair(-d[u], u));
                }
            }
        }
        printf("%d\n", d[t] == INF ? -1 : d[t]);
    }
    return 0;
}

/**

3 3
0 1 1
0 2 3
1 2 1
0 2
3 1
0 1 1
1 2

*/