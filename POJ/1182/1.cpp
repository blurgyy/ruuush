#include<cstdio>
#define maxn 100010

int n, k;
int fa[maxn];

void init()
{
    for(int i = 1; i <= n; i++)fa[i] = i;
}


int Find(int x)
{
    return fa[x] = x ? x : fa[x] = Find(x);
}

void unite(int a, int b)
{
    int f1 = Find(a), f2 = Find(b);
    if(f1 == f2)return;
    fa[f1] = f2;
}

int main()
{
    while(~scanf("%d%d", &n, &k))
    {
        init();
        int d, x, y;
        int a = 0, b = 0, c = 0;
        int ans = 0;
        for(int i = 0; i < k; i++)
        {
            scanf("%d%d%d", &d, &x, &y);
            if(x > n && y > n)
            {
                cnt++;
                continue;
            }
            if(d == 2 && x == y)
            {
                cnt++;
                continue;
            }
            if(a == 0)a = x;
            if(d == 1)
            {
                if(Find(x) )
                if(a != 0 && b != 0 && Find(x) == a && Find(y) == b || b != 0 && c != 0 && Find(x) == b && c != 0 && a != 0 && Find(y) == c || Find(x) == c && Find(y) == a)
                    unite(x, y);

            }
            if(d == 2)
            {
                if(Find(x) == Find(a) && b == 0)b = y;
                else if(c != 0 && Find(y) == Find(c) && b == 0)b = x;
                else if(b != 0 && Find(x) == Find(b) && c == 0)c = y;
                else if(b != 0 && Find(y) == Find(a) && c == 0)c = x;
            }

        }
    }
}
