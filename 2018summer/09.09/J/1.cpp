#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 750050;

int N, M, Q, Tot;
int id[550][550];
int pt;
struct Edge{
    int from, to;
    ll cost;
    void out(){
        printf("from %d to %d cost %lld\n", from, to, cost);
    }
}edge[maxn];
int fa[maxn];

/**/

struct Node{
    int to;
    int w;
    int nxt;
};

Node node[maxn];
int head[maxn];
int top;

void add(int from, int to, int w)
{
    node[top].to = to;
    node[top].w = w;
    node[top].nxt = head[from];
    head[from] = top;
    top ++;
}

///for(int i = head[u]; i != -1; i = node[i].nxt){
///  /// 遍历
///}

void ini()
{
    top = 0;
    memset(head, -1, sizeof(head));
}

/**/
/**/
/**/

bool operator< (Edge a, Edge b){    /********************************************/
    return a.cost > b.cost;
}

void add_edge(int v1, int v2, ll co){
    edge[pt].from = v1;
    edge[pt].to = v2;
    edge[pt++].cost = co;
}

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y){
    int t1 = fa[x], t2 = fa[y];
    if(t1 == t2)return;
    fa[t1] = t2;
}

bool same(int x, int y){
    return find(x) == find(y);
}

void init(){
    ini();
    int idd = 0;
    for(int i = 1; i <= N; ++ i){
        for(int j = 1; j <= M; ++ j){
            id[i][j] = ++ idd;
            //printf("id[%d][%d] = %d\n", i, j, id[i][j]);
        }
    }
    Tot = N * M;
    for(int i = 1; i <= Tot; ++ i){
        fa[i] = i;
    }
    pt = 0;
}

int f[maxn][21],d[maxn];


void Ini()
{
    memset(f, -1, sizeof(f));
    for(int j=1;(1<<j)<=Tot;j++)
    {
        for(int i=1;i<=Tot;i++)
        {
            f[i][j]=f[f[i][j-1]][j-1];
        }
    }
}
int lca(int a,int b)
{
    if(d[a]>d[b])swap(a,b);
    int p=d[b]-d[a];
    for(int i=0;(1<<i)<=p;i++)
        if((1<<i)&p)b=f[b][i];
    if(a!=b)
    {
        for(int i=(int)log2(N);i>=0;i--)
        {
            if(f[a][i]!=f[b][i])
                a=f[a][i],b=f[b][i];
        }
        a=f[a][0];
    }
    return a;
}

void Dfs(int u)
{
    for(int i = head[u]; i != -1; i = node[i].nxt)
    {
        int v=node[i].to;
        if(v==f[u][0])continue;
        d[v]=d[u]+1;
        f[v][0]=u;
        Dfs(v);
    }
}

int main(){
    scanf("%d%d", &N, &M);{
        init();
        char s1[5], s2[5];
        ll v1, v2;
        for(int i = 1; i <= N; ++ i){
            for(int j = 1; j <= M; ++ j){
                scanf("%s%lld%s%lld", s1, &v1, s2, &v2);
                //printf("%s %lld %s %lld!\n", s1, v1, s2, v2);
                if(!strcmp(s1, "D")){
                    //printf("%d %d\n", id[i][j], id[i+1][j]);
                    add_edge(id[i][j], id[i+1][j], v1);
                    add_edge(id[i+1][j], id[i][j], v1);
                }
                if(!strcmp(s2, "R")){
                    add_edge(id[i][j], id[i][j+1], v2);
                    add_edge(id[i][j+1], id[i][j], v2);
                }
            }
        }
        sort(edge, edge + pt);
        for(int i = 0; i < pt; ++ i){
            int a = edge[i].from, b = edge[i].to;
            ll c = edge[i].cost;
            if(same(a, b))continue;
            unite(a, b);
            add(a, b, c);
            add(b, a, c);
            //add_edge(a, b, c);
        }

        int root = 1;
        //for(int i = 1; i <= Tot; ++ i){
        //    printf("dep[%d] = %d\n", i, dep[i]);
        //}
        d[root] = 1;
        Dfs(root);
        Ini();
        scanf("%d", &Q);

        for(int i=1;i<=Q;++i){
            int x, y;
            int i1, i2, i3, i4;
            scanf("%d%d%d%d", &i1, &i2, &i3, &i4);
            x = id[i1][i2];
            y = id[i3][i4];
            printf("%d\n", d[x] + d[y] - 2 * d[lca(x, y)]);
        }
    }
    return 0;
}

/**

3 3
D 1 R 9
D 7 R 8
D 4 X 0
D 2 R 6
D 12 R 5
D 3 X 0
X 0 R 10
X 0 R 11
X 0 X 0
1000
1 1 3 3
1 2 3 2
2 2 3 1

*/
