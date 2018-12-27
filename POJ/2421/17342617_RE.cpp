#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define maxn 110
using namespace std;

int n, q;
int mp[maxn][maxn];
int fa[maxn];

struct edge
{
    int start, dest, cost;
}E[maxn];
int pointer = 0;

bool operator < (edge a, edge b)
{
    return a.cost < b.cost;
}

int Find(int x)
{
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

void unite(int a, int b)
{
    int t1 = Find(a), t2 = Find(b);
    if(t1 == t2)return;
    fa[t1] = t2;
}

bool Same(int a, int b)
{
    return Find(a) == Find(b);
}

void init()
{
    for(int i = 0; i < maxn; i++)fa[i] = i;
    memset(mp, 0, sizeof(mp));
    pointer = 0;
}

void add_edge(int a, int b, int cost)
{
    E[pointer].start = a;
    E[pointer].dest = b;
    E[pointer++].cost = cost;
}

int main()
{
    scanf("%d", &n);
    init();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%d", mp[i] + j);
    scanf("%d", &q);
    int a, b;
    while(q--)
    {
        scanf("%d%d", &a, &b);
        mp[a][b] = 0;
        unite(a, b);
    }
    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++)
            add_edge(i, j, mp[i][j]);
    sort(E, E + pointer);
    int ans = 0;
    for(int i = 0; i < pointer; i++)
    {
        int a = E[i].start, b = E[i].dest, c = E[i].cost;
        if(Same(a, b))continue;
        unite(a, b);
        ans += c;
    }
    printf("%d\n", ans);
    return 0;
}
