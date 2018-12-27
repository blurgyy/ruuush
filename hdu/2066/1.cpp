#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int INF = 0x3f3f3f3f;

int t, s, d;
int a, b, Time;
int start[maxn], End[maxn];
int dist[maxn], ans;
priority_queue<pair<int, int> > Q;
vector<pair<int, int> > E[maxn];

void add_edge(int u, int v, int cost){
    E[u].push_back(make_pair(v, cost));
    E[v].push_back(make_pair(u, cost));
}

void init(){
    for(int i = 0; i < maxn; ++ i)  //I forgot this.. twice in less than 12 hours
        E[i].clear();               //And got 3 wrong answers for this one stupid mistake
    memset(dist, 0x3f, sizeof(dist));
    memset(start, 0, sizeof(start));
    memset(End, 0, sizeof(End));
    ans = INF;
}

int main(){
    while(~scanf("%d%d%d", &t, &s, &d)){
        init();
        while(t--){
            scanf("%d%d%d", &a, &b, &Time);
            add_edge(a, b, Time);
        }
        for(int i = 0; i < s; ++ i){
            scanf("%d", start + i);
        }
        for(int i = 0; i < d; ++ i){
            scanf("%d", End + i);
        }
        for(int I = 0; I < s; ++ I){
            memset(dist, 0x3f, sizeof(dist));
            int nows = start[I];
            dist[nows] = 0;
            Q.push(make_pair(-dist[nows], nows));
            while(!Q.empty()){
                int now = Q.top().second;
                Q.pop();
                int len = E[now].size();
                for(int i = 0; i < len; ++ i){
                    int u = E[now][i].first;
                    if(dist[u] > dist[now] + E[now][i].second){
                        dist[u] = dist[now] + E[now][i].second;
                        Q.push(make_pair(-dist[u], u));
                    }
                }
            }
            for(int i = 0; i < d; ++ i)
                ans = min(ans, dist[End[i]]);
        }
        printf("%d\n", ans);
    }
    return 0;
}