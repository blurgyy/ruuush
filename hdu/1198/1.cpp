///注意要两边都连通才能连通
///左边连而右边不连是不行的
///下次看

#include<cstdio>
#include<cstring>
#define maxn 3010
using namespace std;

int m, n, ans;
int fa[maxn];
char mp[60][60];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int num[60][60];
int p = 1;

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
    for(int i = 1; i <= n*m; i++)
        fa[i] = i;
    memset(mp, 0, sizeof(mp));
    ans = 0;
}

bool check_edge(int x, int y)
{
    if(x == 0 || y == 0 || x == m + 1 || y == n + 1)return true;
    return false;
}

void in()
{
    for(int i = 1; i <= m; i++)
        scanf("%s", mp[i] + 1);
}

int main()
{
    for(int i = 1; i <= 60; i++)
        for(int j = 1; j <= 60; j++)
            num[i][j] = p++;
    while(~scanf("%d%d", &m, &n) && (n != -1 && m != -1))
    {
        init();
        in();
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++)
            {
                if(mp[i][j] == 'A')
                {
                    if(!check_edge(i-1, j))unite(num[i][j], num[i-1][j]);
                    if(!check_edge(i, j-1))unite(num[i][j], num[i][j-1]);
                }
                if(mp[i][j] == 'B')
                {
                    if(!check_edge(i-1, j))unite(num[i][j], num[i-1][j]);
                    if(!check_edge(i, j+1))unite(num[i][j], num[i][j+1]);
                }
                if(mp[i][j] == 'C')
                {
                    if(!check_edge(i+1, j))unite(num[i][j], num[i+1][j]);
                    if(!check_edge(i, j-1))unite(num[i][j], num[i][j-1]);
                }
                if(mp[i][j] == 'D')
                {
                    if(!check_edge(i+1, j))unite(num[i][j], num[i+1][j]);
                    if(!check_edge(i, j+1))unite(num[i][j], num[i][j+1]);
                }
                if(mp[i][j] == 'E')
                {
                    if(!check_edge(i-1, j))unite(num[i][j], num[i-1][j]);
                    if(!check_edge(i+1, j))unite(num[i][j], num[i+1][j]);
                }
                if(mp[i][j] == 'F')
                {
                    if(!check_edge(i, j-1))unite(num[i][j], num[i][j-1]);
                    if(!check_edge(i, j+1))unite(num[i][j], num[i][j+1]);
                }
                if(mp[i][j] == 'G')
                {
                    if(!check_edge(i-1, j))unite(num[i][j], num[i-1][j]);
                    if(!check_edge(i, j-1))unite(num[i][j], num[i][j-1]);
                    if(!check_edge(i, j+1))unite(num[i][j], num[i][j+1]);
                }
                if(mp[i][j] == 'H')
                {
                    if(!check_edge(i-1, j))unite(num[i][j], num[i-1][j]);
                    if(!check_edge(i, j-1))unite(num[i][j], num[i][j-1]);
                    if(!check_edge(i+1, j))unite(num[i][j], num[i+1][j]);
                }
                if(mp[i][j] == 'I')
                {
                    if(!check_edge(i, j+1))unite(num[i][j], num[i][j+1]);
                    if(!check_edge(i, j-1))unite(num[i][j], num[i][j-1]);
                    if(!check_edge(i+1, j))unite(num[i][j], num[i+1][j]);
                }
                if(mp[i][j] == 'J')
                {
                    if(!check_edge(i, j+1))unite(num[i][j], num[i][j+1]);
                    if(!check_edge(i-1, j))unite(num[i][j], num[i-1][j]);
                    if(!check_edge(i+1, j))unite(num[i][j], num[i+1][j]);
                }
                if(mp[i][j] == 'J')
                {
                    if(!check_edge(i, j+1))unite(num[i][j], num[i][j+1]);
                    if(!check_edge(i-1, j))unite(num[i][j], num[i-1][j]);
                    if(!check_edge(i+1, j))unite(num[i][j], num[i+1][j]);
                    if(!check_edge(i, j-1))unite(num[i][j], num[i][j-1]);
                }
            }
        for(int i = 1; i <= n*m; i++)
            if(fa[i] == i)ans++;
        printf("%d\n", ans);
    }
}
