#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 110;
const int maxm = 1010;
const int mod = 31011;

int n, m;
int fa[maxn], glo[maxn];
vector<int> tree[maxn];
bool vis[maxn];
int cnt[maxn][maxn];
ll kirch[maxn][maxn];
struct Edge{
    int u, v, w;
    void set(int _u, int _v, int _w){
        u = _u, v = _v, w = _w;
    }
    // bool operator< (Edge rhs){
    //     return w < rhs.w;
    // }
}E[maxm];
// bool operator< (Edge &a, Edge &b){ // CE
bool operator< (Edge a, Edge b){
    return a.w < b.w;
}

int find(int x, int fa[]){return x == fa[x] ? x : find(fa[x], fa);}
bool same(int x, int y, int fa[]){return find(x, fa) == find(y, fa);}
void unite(int x, int y, int fa[]){
    int t1 = find(x, fa), t2 = find(y, fa);
    if(t1 == t2) return;
    fa[t1] = t2;
}

ll det(ll a[][maxn], int n){
    ll ret = 1;
    for(int i = 0; i < n; ++ i){    // using the i-th row to eliminate the corresponding elements in the following rows
        for(int j = i+1; j < n; ++ j){  // for every row after the i-th row
            int x = i;
            int y = j;
            while(a[y][i]){ // 辗转相除
                ll t = a[x][i] / a[y][i];
                for(int k = i; k < n; ++ k){
                    // a[x][k] -= t * a[y][k];
                    a[x][k] = (a[x][k] - t * a[y][k]) % mod;
                }
                swap(x, y);
            }
            if(x != i){ // 交换奇数次
                for(int k = i; k < n; ++ k){
                    swap(a[x][k], a[y][k]);
                }
                ret *= -1;  // 答案符号改变
            }
        }
        if(a[i][i] == 0){   // 本行消元后若对角线元素为 0 则答案为 0 
            return 0;
        }
        // ret *= a[i][i];
        ret = ret * a[i][i] % mod;
    }
    // printf(">>> ret = %lld\n", ret);
    return (ret + mod) % mod;
}

void ini(){
    for(int i = 0; i < maxn; ++ i) fa[i] = i;
    for(int i = 0; i < maxn; ++ i) glo[i] = i;
    // memset(cnt, 0, sizeof(cnt));
    memset(vis, false, sizeof(vis));
}

int main(){
    // while(~scanf("%d%d", &n, &m)){
    ios::sync_with_stdio(false);
    while(cin >> n >> m){
        ini();
        for(int i = 0, u, v, w; i < m; ++ i){
            // scanf("%d%d%d", &u, &v, &w);
            cin >> u >> v >> w;
            // add_edge(u, v, w);
            E[i].set(u, v, w);
        }
        sort(E, E + m);
        int last = -1;
        ll ans = 1;
        for(int i = 0; i <= m; ++ i){
            int u = E[i].u;
            int v = E[i].v;
            int w = E[i].w;
            if(w != last){
                for(int i = 1; i <= n; ++ i){
                    tree[i].clear();
                }
                for(int j = 1; j <= n; ++ j){
                    if(vis[j]){
                        int root = find(j, glo);
                        tree[root].push_back(j);
                        vis[j] = false;
                    }
                }
                for(int j = 1; j <= n; ++ j){
                    int len = tree[j].size();
                    // printf("len = %d\n", len);
                    if(len > 1){
                        // construct a Kirchhoff matrix
                        memset(kirch, 0, sizeof(kirch));
                        for(int x = 0; x < len; ++ x){
                            for(int y = x + 1; y < len; ++ y){
                                int u = tree[j][x];
                                int v = tree[j][y];
                                int t = cnt[u][v];
                                // printf("(%d, %d)\n", u, v);
                                kirch[x][x] += t;
                                kirch[y][y] += t;
                                kirch[x][y] -= t;
                                kirch[y][x] -= t;
                            }
                        }
                        // for(int k = 0; k < len; ++ k){
                        //     for(int l = 0; l < len; ++ l){
                        //         printf("%3lld ", kirch[k][l]);
                        //     }
                        //     printf("\n");
                        // }
                        // printf("-----\n");
                        // calculate
                        ans = ans * det(kirch, len - 1) % mod;
                    }
                    for(int k = 0; k < len; ++ k){
                        unite(j, tree[j][k], fa);
                    }
                }

                memset(cnt, 0, sizeof(cnt));
                for(int j = 1; j <= n; ++ j){   // 延迟更新
                    fa[j] = find(j, glo);
                }
                last = w;
            }
            /**/
            if(same(u, v, fa)) continue;
            unite(u, v, glo);
            int t1 = find(u, fa);
            int t2 = find(v, fa);
            // printf("(%d, %d) not united, root (%d, %d)\n", u, v, t1, t2);
            vis[t1] = vis[t2] = true;
            cnt[t1][t2] ++;
            cnt[t2][t1] ++;
            // cnt[u][v] ++;
            // cnt[v][u] ++;
        }
        int root = find(1, glo);
        for(int i = 1; i <= n; ++ i){
            if(find(i, glo) != find(root, glo)){
                ans = 0;
                break;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
