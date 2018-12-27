//I'll try floyd... Doubt it

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int INF = 0x3f3f3f3f;

int n, m, s;
int u, v, cost;
int w, start;
int ans = INF;
int edge[maxn][maxn];

void add_edge(){
    edge[u][v] = edge[v][u] = min(edge[u][v], cost);
}

void init(){
    memset(edge, 0x3f, sizeof(edge));
    for(int i = 0; i < maxn; ++ i)
        edge[i][i] = 0;
}

void out(){
    for(int i = 0; i < n; ++ i){
        for(int j = 0; j < n; ++ j)
            printf("%11d", edge[i][j]);
        printf("\n");
    }
}

int main(){
    while(~scanf("%d%d%d", &n, &m, &s)){
        init();
        while(m--){
            scanf("%d%d%d", &u, &v, &cost);
            add_edge();
        }
        out();
        for(int k = 0; k < n; ++ k){
            for(int i = 0; i < n; ++ i){
                for(int j = 0; j < n; ++ j){
                    edge[i][j] = min(edge[i][j], edge[i][k] + edge[k][j]);
                }
            }
        }
        out();
        scanf("%d", &w);
        while(w--){
            scanf("%d", &start);
            ans = min(ans, edge[start][s]);
        }
        if(ans < INF)printf("%d\n", ans);
        else printf("-1\n");
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