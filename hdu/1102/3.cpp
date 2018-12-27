#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1010
#define ll long long
using namespace std;

int n, q;
int fa[maxn];
int mp[maxn][maxn];

struct edge
{
    int from, to, cost;
}E[maxn*maxn];
int p;

bool operator < (edge a, edge b)
{
    return a.cost < b.cost;
}

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

void init()
{
    for(int i = 0; i < maxn; i++)fa[i] = i;
    memset(mp, 0, sizeof(mp));
    p = 0;
}

int main()
{
    while(~scanf("%d", &n)){
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
            mp[b][a] = 0;
        }
        for(int i = 1; i <= n; i++)
            for(int j = i+1; j <= n; j++)
            {
                E[p].from = i;
                E[p].to = j;
                E[p++].cost = mp[i][j];
            }
        /*
        for(int i = 0; i < p; i++)
            printf("%d %d %d\n", E[i].from, E[i].to, E[i].cost);
        */
        ll ans = 0;
        sort(E, E + p);
        for(int i = 0; i < p; i++)
        {
            int a = E[i].from, b = E[i].to, c = E[i].cost;
            //printf("%d %d %d\n", a, b, c);
            if(Same(a, b))continue;
            unite(a, b);
            ans += c;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
/**
3
0 990 692
990 0 179
692 179 0
1
1 2
*/
