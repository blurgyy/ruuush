#include<cstdio>
#include<cstring>
#define maxn 30010

int n, m;
int fa[maxn];
int student[maxn];

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
    for(int i = 0; i < n; i++)fa[i] = i;
    memset(student, 0, sizeof(student));
}

int main()
{
    while(~scanf("%d%d", &n, &m) && (n || m))
    {
        init();
        int k;
        int tmp;
        while(m--)
        {
            scanf("%d", &k);
            for(int i = 0; i < k; i++)
            {
                scanf("%d", &tmp);
                if(i == 0)
                {
                    student[i] = tmp;
                    continue;
                }
                else
                {
                    unite(tmp, student[i-1]);
                    student[i] = tmp;
                }
            }
        }
/*
        for(int i = 0; i < n; i++)
            printf("%3d", fa[i]);
        printf("\n");
*/
        int ans = 0;
        for(int i = 0; i < n; i++)
            if(fa[i] == 0 || fa[i] == fa[0])ans++;
        printf("%d\n", ans);
    }
    return 0;
}
