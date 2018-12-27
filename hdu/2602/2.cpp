#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1010
#define ll long long
using namespace std;

int t;
int n, v;
ll val[maxn], wei[maxn];
ll dp[maxn][maxn];

void init()
{
    memset(val, 0, sizeof(val));
    memset(wei, 0, sizeof(wei));
    memset(dp, 0, sizeof(dp));
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &v);
        init();
        for(int i = 1; i <= n; i++)scanf("%lld", val + i);
        for(int i = 1; i <= n; i++)scanf("%lld", wei + i);
        for(int i = 1; i <= n; i++)
        {
            for(int j = 0; j <= v; j++)
            {
                if(j < wei[i])dp[i][j] = dp[i-1][j];
                else
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-wei[i]] + val[i]);
            }
        }
        printf("%lld\n", dp[n][v]);
    }
    return 0;
}
