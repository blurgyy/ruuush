#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 10010
using namespace std;

int t, n;
double p;
double prob[maxn];
double dp[maxn];
int mon[maxn];

void init()
{
    memset(prob, 0, sizeof(prob));
    memset(mon, 0, sizeof(mon));
    memset(dp, 1, sizeof(dp));
    //dp[0] = 1;
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%lf%d", &p, &n);
        init();
        for(int i = 1; i <= n; i++)
            scanf("%d%lf", mon + i, prob + i);
        for(int i = 1; i <= n; i++)
        {
            for(int j = 10000; j > 0; j--)
            {
                if(j > mon[i])dp[j] = max(dp[j], dp[j-mon[i]] - prob[i]);
            }
        }
        for(int i = 1; i <= 100; i++)
            printf("%5.2lf", dp[i]);
        printf("\n");
    }
    return 0;
}
