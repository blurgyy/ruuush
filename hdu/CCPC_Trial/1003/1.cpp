#include<cstdio>
#include<cstring>
#define maxn 5100

int T;
int n;
int rel[maxn][maxn];

int fa[maxn];

int Find(int x)
{
    return fa[x] == x ? x : Find(fa[x]);
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

void initialze()
{
    memset(rel, 0, sizeof(rel));
    for(int i = 0; i < maxn; i++)fa[i] = i;
}

int main()
{
    while(~scanf("%d", &T))
    {
        while(T--)
        {
            initialze();
            scanf("%d", &n);
            for(int i = 1; i <= n; i++)
                for(int j = 1; j <= n-i; j++)
                    scanf("%d", rel[i] + j);

        }
    }
}
