#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 110;
const int maxm = 1010;
// const int maxk = 20;
const int mod = 31011;
const int inf = 0x3f3f3f3f;

int n, m;
ll kirch[maxn][maxn];
int mat[maxn][maxn];
struct Edge{
    Edge(int _u = 0, int _v = 0, int _w = 0):
        u(_u), v(_v), w(_w){}
    int u, v, w;
    bool operator< (Edge &rhs){
        return w < rhs.w;
    }
}E[maxm];

void out(ll a[][4], int n){
    for(int i = 0; i < n; ++ i){
        for(int j = 0; j < n; ++ j){
            printf("%3lld ", a[i][j]);
        }
        printf("\n");
    }
}

ll det(ll a[][4],int n){//生成树计数
    out(a, n);
    // printf("det\n");
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)a[i][j]%=mod;
    ll ret=1;
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
            while(a[j][i])
            {
                ll t=a[i][i]/a[j][i];
                for(int k=i;k<n;k++)
                    a[i][k]=(a[i][k]-a[j][k]*t)%mod;
                for(int k=i;k<n;k++)
                    swap(a[i][k],a[j][k]);
                ret=-ret;
            }
        if(a[i][i]==0){
            out(a, 4);
            return 0;
        }
        ret=ret*a[i][i]%mod;
    }
    out(a, 4);
    ret = (ret+mod)%mod;
    printf("ret = %lld\n", ret);
    return ret;
}

// ll det(int a[][maxk], int n){
//     for(int i = 0; i < n; ++ i){
//         for(int j = 0; j < n; ++ j){
//             a[i][j] %= mod;
//         }
//     }
//     for(int i = 1; i < n; ++ i){
//         for(int j = i+1; j < n; ++ j){

//         }
//     }
// }

int main(){
    while(~scanf("%d%d", &n, &m)){
        for(int i = 0, u, v, w; i < m; ++ i){
            scanf("%d%d%d", &u, &v, &w);
            mat[u][v] = mat[v][u] = w;
            E[i] = Edge(u, v, w);
        }
        for(int i = 0; i < n; ++ i){
            for(int j = 0; j < n; ++ j){
                printf("%3d", mat[i][j]);
            }
            printf("\n");
        }
        printf("---\n");
        E[m] = Edge(-1, -1, inf);
        sort(E, E + m);
        int now = -1;
        ll ans = 1;
        vector<Edge> rec;
        for(int i = 0; i <= m; ++ i){
            if(E[i].w != now){
                int cnt = rec.size();
                if(cnt == 0){
                    rec.push_back(E[i]);
                    now = E[i].w;
                    continue;
                }
                memset(kirch, 0, sizeof(kirch));
                for(int j = 0; j < cnt; ++ j){
                    int u = rec[j].u;
                    int v = rec[j].v;
                    kirch[u][u] += 1;
                    kirch[v][v] += 1;
                    kirch[u][v] -= 1;
                    kirch[v][u] -= 1;
                }
                ans = ans * det(kirch, n) % mod;
                // printf("ans = %lld\n", ans);
                now = E[i].w;
                rec.clear();
            }
            rec.push_back(E[i]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
