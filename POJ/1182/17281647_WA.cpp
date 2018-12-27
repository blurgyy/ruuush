#include<cstdio>
#include<cstring>
#define maxn 200010

int n, k;
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
    while(~scanf("%d%d", &n, &k))
    {
        init();
        int d, x, y;
        int ans = 0;
        while(k--)
        {
            scanf("%d%d%d", &d, &x, &y);
            if((d == 2 && x == y )|| x > n || y > n)
            {
                ans++;
                continue;
            }
            if(d == 1)
            {
                if(Find(x) == Find(y + n) || Find(x + n) == Find(y))ans++;
                else
                {
                    unite(x, y);
                    unite(x + n, y + n);
                    unite(x + 2 * n, y + 2 * n);
                }
            }
            else
            {
                if(Find(x) == Find(y) || Find(x + n) == Find(y))ans++;
                else
                {
                    unite(x, y + n);
                    unite(x + n, y + 2 * n);
                    unite(x + 2 * n, y);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
