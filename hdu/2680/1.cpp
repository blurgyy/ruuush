#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int maxm = 20010;
const int INF = 0x3f3f3f3f;

int n, m, s;
int u, v, cost;
int w, start;
int d[maxn];
int ans;
vector<pair<int, int> > E[maxm];
priority_queue<pair<int, int> > Q;

void add_edge(){
    E[u].push_back(make_pair(v, cost));
    E[v].push_back(make_pair(u, cost));
}

void init(){
    for(int i = 0; i < maxm; ++ i)
        E[i].clear();
    memset(d, 0x3f, sizeof(d));
    ans = INF;
}

int main(){
    while(~scanf("%d%d%d", &n, &m, &s)){
        init();
        while(m--){
            scanf("%d%d%d", &u, &v, &cost);
            add_edge();
        }
        scanf("%d", &w);
        while(w--){
            scanf("%d", &start);
            memset(d, 0x3f, sizeof(d));
            d[start] = 0;
            Q.push(make_pair(-d[start], start));
            while(!Q.empty()){
                int now = Q.top().second;
                int len = E[now].size();
                Q.pop();
                for(int i = 0; i < len; ++ i){
                    int v = E[now][i].first;
                    if(d[v] > d[now] + E[now][i].second){
                        d[v] = d[now] + E[now][i].second;
                        Q.push(make_pair(-d[v], v));
                    }
                }
            }
            ans = min(ans, d[s]);
        }
        printf("%d\n", ans == INF ? -1 : ans);
    }
    return 0;
}

/**

5 8 5
1 2 2
1 5 3
1 3 4
2 4 7
2 5 6
2 3 5
3 5 1
4 5 1
2
2 3
4 3 4
1 2 3
1 3 4
2 3 2
1
1


*/