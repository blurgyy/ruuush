#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1010
using namespace std;

int t;
int n, v;
int weight[maxn], value[maxn];
int dp[maxn][maxn];

int main()
{
    while(~scanf("%d", &t))
    {
        while(t--)
        {
            scanf("%d%d", &n, &v);
            for(int i = 1; i <= n; i++)
                scanf("%d", value + i);
            for(int i = 1; i <= n; i++)
                scanf("%d", weight + i);
            memset(dp, 0, sizeof(dp));
            for(int i = 1; i <= n; i++)
            {
                for(int j = weight[i]; j <= v; j++)
                    dp[i][j] = max(dp[i][j], dp[i-1][j-weight[i]] + value[i]);
            }
            printf("%d\n", dp[n][v]);
        }
    }
    return 0;
}
