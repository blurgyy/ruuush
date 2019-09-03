#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
const int maxm = 1000010;
const int inf = 0x3f3f3f3f;

int n, m;
int p[maxm];
char edge[maxn][maxn];
int d[maxn][maxn];
int pl[maxm], pr[maxm];

int find(int fa[], int x){return fa[x] == x ? x : find(fa, fa[x]);}
bool same(int fa[], int x, int y){return find(fa, x) == find(fa, y);}
void unite(int fa[], int x, int y){
    int f1 = find(fa, x), f2 = find(fa, y);
    if(f1 == f2) return;
    fa[f1] = f2;
    // printf("unite: %d -> %d\n", f1, f2);
}

void extend(int pos, int l, int r){
    if(pos == 1 || pos == m) return;
    // printf("%d -> %d\n", l, find(pl, l));
    // printf("%d -> %d\n", r, find(pr, r));
    l = find(pl, l);
    r = find(pr, r);
    if(p[l] == -1 || p[r] == -1){
        return;
    }
    if(d[p[l]][p[r]] == r - l){
        // printf("d[%d][%d] = %d\n", p[l], p[r], d[p[l]][p[r]]);
        p[pos] = -1;
        // printf("p[%d] = -1\n", pos);
        unite(pl, pos, l);
        unite(pr, pos, r);
        int nl = max(1, l-1);
        int nr = min(r+1, m);
        extend(l, nl, r);
        extend(r, l, nr);
    }
}

void init(){
    for(int i = 0; i < maxm; ++ i){
        pl[i] = pr[i] = i;
    }
}

int main(){
    // freopen("in.in", "r", stdin);
    while(~scanf("%d", &n)){
        init();
        for(int i = 1; i <= n; ++ i){
            scanf("%s", edge[i]+1);
        }
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= n; ++ j){
                if(edge[i][j] == '1'){
                    d[i][j] = 1;
                }
                else {
                    d[i][j] = inf;
                }
            }
        }
        scanf("%d", &m);
        for(int i = 1; i <= m; ++ i){
            scanf("%d", p + i);
        }
        for(int k = 1; k <= n; ++ k){
            d[k][k] = 0;
            for(int i = 1; i <= n; ++ i){
                for(int j = 1; j <= n; ++ j){
                    // printf("d[%d][%d] = %d\n", i, j, d[i][j]);
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    // printf("d[%d][%d] = %d\n", i, j, d[i][j]);
                    // printf("\n");
                }
            }
        }
        // for(int i = 1; i <= n; ++ i){
        //     for(int j = 1; j <= n; ++ j){
        //         printf("%12d", d[i][j]);
        //     }
        //     printf("\n");
        // }
        for(int i = 2; i < m; ++ i){
            extend(i, i-1, i+1);
        }
        int cnt = 0;
        for(int i = 1; i <= m; ++ i){
            cnt += p[i] != -1;
        }
        printf("%d\n", cnt);
        for(int i = 1; i <= m; ++ i){
            if(p[i] == -1){
                continue;
            }
            printf("%d%c", p[i], " \n"[i==m]);
        }
    }
    return 0;
}
