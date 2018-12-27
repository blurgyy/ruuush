#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 2005
using namespace std;

int n;
int fa[maxn];
int ans;
char code[maxn][10];
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

struct edge
{
    int start, dest, cost;
}E[maxn*maxn];

void init()
{
    for(int i = 0; i < maxn; i++)fa[i] = i;
    p = 0;
    ans = 0;
}

int ret_dif(char a[], char b[])
{
    int ans = 0;
    for(int i = 0; i < 7; i++)
        if(a[i] != b[i])++ans;
    return ans;
}

void add_edge(int a, int b, int c)
{
    E[p].start = a;
    E[p].dest = b;
    E[p++].cost = c;
    E[p].start = b;
    E[p].dest = a;
    E[p++].cost = c;
}

bool operator < (edge a, edge b)
{
    return a.cost < b.cost;
}

bool Same(int x, int y)
{
    return Find(x) == Find(y);
}

int main()
{
    while(~scanf("%d", &n) && n)
    {
        init();
        for(int i = 0; i < n; i++)
            scanf("%s", code[i]);
        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                add_edge(i, j, ret_dif(code[i], code[j]));
        sort(E, E + p);
        for(int i = 0; i < p; i++)
        {
            int a = E[i].start, b = E[i].dest, c = E[i].cost;
            if(Same(a, b))continue;
            unite(a, b);
            ans += c;
        }
        printf("The highest possible quality is 1/%d.\n", ans);
    }
    return 0;
}
