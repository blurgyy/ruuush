#include<cstdio>
#include<cstring>
#define maxn 200
#include<algorithm>
using namespace std;

int n, m;
char mp[maxn][maxn];
int cnt;
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

void dfs(int x, int y)
{
    mp[x][y] = '*';
    for(int d = 0; d < 8; d++)
    {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if(mp[nx][ny] == '@')dfs(nx, ny);
    }
}

void in()
{
    getchar();
    for(int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
}

void out()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
            printf("%c", mp[i][j]);
        printf("\n");
    }
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        if(n == 0 && m == 0)break;
        memset(mp, 0, sizeof(mp));
        cnt = 0;
        ///printf("n = %d, m = %d\n", n, m);
        in();
        ///out();
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                if(mp[i][j] == '@')
                {
                    cnt++;
                    dfs(i, j);
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}

/**

5 5
****@
*@@*@
*@**@
@@@*@
@@**@

*/
