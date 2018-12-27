#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 110
using namespace std;

int n, q;
int fa[maxn];
int mat[maxn][maxn];

struct edge
{
    int start, dest, cost;
}E[maxn * maxn];
int p;

int Find(int x)
{
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

void unite(int x, int y)
{
    int t1 = Find(x), t2 = Find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

bool Same(int x, int y)
{
    return Find(x) == Find(y);
}

void add_edge(int x, int y, int dist)
{
    E[p].start = x;
    E[p].dest = y;
    E[p++].cost = dist;
    E[p].start = y;
    E[p].dest = x;
    E[p++].cost = dist;
}

void init()
{
    for(int i = 0; i < maxn; i++)fa[i] = i;
    memset(mat, 0, sizeof(mat));
    for(int i = 0; i < maxn * maxn; i++)E[i].cost = 0;
    p = 0;
}

bool operator < (edge a, edge b)
{
    return a.cost < b.cost;
}

int main()
{
    scanf("%d", &n);
    init();
    int ans = 0;
    int dist;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%d", mat[i] + j);
    scanf("%d", &q);
    int a, b;
    while(q--)
    {
        scanf("%d%d", &a, &b);
        mat[a][b] = 0;
        mat[b][a] = 0;
    }

    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++)
            add_edge(i, j, mat[i][j]);

    sort(E, E + p);
    for(int i = 0; i < p; i++)
    {
        int a = E[i].start, b = E[i].dest, c = E[i].cost;
        if(Same(a, b))continue;
        unite(a, b);
        ans += c;
    }
    printf("%d\n", ans);
}

/**

3
0 990 200
990 0 179
200 179 0
1
1 2

*/
