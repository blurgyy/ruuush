#include<cstdio>
#include<cstring>
#define maxn 30010
#include<algorithm>
using namespace std;

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
    Find(y);
}

void init()
{
    for(int i = 0; i < n; i++)fa[i] = i;
    memset(student, 0, sizeof(student));
}

void out()
{
    for(int i = 0; i < 15; i++)
        printf("%3d", fa[i]);
    printf("\n");
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
                scanf("%d", student + i);
            sort(student, student + k);
            for(int i = 1; i < k; i++)
                unite(student[i], student[i-1]);
        }
        int ans = 0;
        for(int i = 0; i < n; i++)
            if(Find(i) == Find(0))ans++;
        printf("%d\n", ans);
    }
    return 0;
}
