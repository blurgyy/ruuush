#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxp 610
#define maxn 10010
using namespace std;

int p, r;
int fa[maxp];

struct edge
{
    int start, dest, cost;
}E[maxn];
int pointer;

int Find(int x)
{
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

void unite(int x, int y)
{
    int f1 = Find(x), f2 = Find(y);
    if(f1 == f2)return;
    fa[f1] = f2;
}

int init()
{
    for(int i = 0; i < maxp; i++)
        fa[i] = i;
    for(int i = 0; i < maxn; i++)
    {
        E[i].start = 0;
        E[i].dest = 0;
        E[i] .cost = 0;
    }
    pointer = 0;
}

void add_edge(int x, int y, int d)
{
    E[pointer].start = x;
    E[pointer].dest = y;
    E[pointer++].cost = d;
    E[pointer].start = y;
    E[pointer].dest = x;
    E[pointer++].cost = d;
}

bool operator < (edge a, edge b)
{
    return a.cost < b.cost;
}

bool same(int x, int y)
{
    return Find(x) == Find(y);
}

int main()
{
    while(~scanf("%d", &p) && p)
    {
        scanf("%d", &r);
        init();
        int x, y, d;
        int ans = 0;
        while(r--)
        {
            scanf("%d%d%d", &x, &y, &d);
            add_edge(x, y, d);
        }
        sort(E, E + pointer);
        for(int i = 0; i < pointer; i++)
        {
            int a = E[i].start, b = E[i].dest;
            if(same(a, b))continue;
            ans += E[i].cost;
            unite(a, b);
        }
        printf("%d\n", ans);
    }
    return 0;
}
