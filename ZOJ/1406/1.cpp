#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define maxn 30
#define maxedge 80
using namespace std;

int n;
int fa[maxn];
map<char, int> alpha;
int pt;
int ans;

struct edge
{
    int start, dest, cost;
}E[maxedge];

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

void add_edge(int x, int y, int z)
{
    E[pt].start = x;
    E[pt].dest = y;
    E[pt++].cost = z;
}

bool operator < (edge a, edge b)
{
    return a.cost < b.cost;
}

void init()
{
    for(int i = 0; i < maxn; i++)fa[i] = i;
    pt = 0;
    ans = 0;
}

int main()
{
    for(int i = 1; i < 27; i++)alpha['A'-1+i] = i;
    while(~scanf("%d", &n) && n)
    {
        init();
        n--;
        char vill[5];
        int cases;
        while(n--)
        {
            scanf("%s%d", vill, &cases);
            int u = alpha[vill[0]];
            int cost;
            while(cases--)
            {
                scanf("%s%d", vill, &cost);
                int v = alpha[vill[0]];
                add_edge(u, v, cost);
            }
        }
        sort(E, E + pt);
        for(int i = 0; i < pt; i++)
        {
            int a = E[i].start, b = E[i].dest, c = E[i].cost;
            if(Same(a, b))continue;
            unite(a, b);
            ans += c;
        }
        printf("%d\n", ans);
    }
    return 0;
}
