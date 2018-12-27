#include<cstdio>
#include<cstring>
#define maxn 1010

int n, m, t;
int fa[maxn];

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

void init()
{
    for(int i = 1; i <= n; i++)
        fa[i] = i;
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        init();
        int a, b;
        int ans = 0;
        while(m--)
        {
            scanf("%d%d", &a, &b);
            unite(a, b);
        }
        for(int i = 1; i <= n; i++)
            if(fa[i] == i)ans++;
        printf("%d\n", ans);
    }
    return 0;
}
