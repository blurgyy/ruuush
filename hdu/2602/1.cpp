#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1010
#define ll long long
using namespace std;

int t;
int n, v;
ll val[maxn], wei[maxn];
ll dp[maxn];

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
            for(int j = v; j >= wei[i]; j--)
                dp[j] = max(dp[j], dp[j-wei[i]] + val[i]);
        printf("%lld\n", dp[v]);
    }
    return 0;
}
