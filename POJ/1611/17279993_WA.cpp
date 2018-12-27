#include<cstdio>
#include<cstring>
#define maxn 30010

int n, m, k;
int parent[maxn];
int student[maxn];

int Find(int x, int cnt)
{
    if(parent[x] < 0)
    {
        parent[x] = -cnt;
        return x;
    }
    cnt++;
    return parent[x] = Find(parent[x], cnt);
    //return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void unite(int x, int y)
{
    int r1 = Find(x, 1), r2 = Find(y, 1);
    if(r1 == r2)return;
    int tmp = parent[r1] + parent[r2];
    if(r1 == 0)
    {
        parent[r2] = r1;
        parent[r1] = tmp;
    }
    else
    {
        parent[r1] = r2;
        parent[r2] = tmp;
    }
}

void init()
{
    for(int i = 0; i < n; i ++)
        parent[i] = -1;
}

int main()
{
    while(~scanf("%d%d", &n, &m) && (n || m))
    {
        init();
        while(m--)
        {
            scanf("%d", &k);
            for(int i = 0; i < k; i++)
                scanf("%d", student + i);
            for(int i = 1; i < k; i++)
                unite(student[i], student[i-1]);
        }
        printf("%d\n", -parent[0]);
    }
    return 0;
}
