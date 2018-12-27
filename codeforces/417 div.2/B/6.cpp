#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n, m;
char building[20][110];
int l[150], r[150];

void input()
{
    memset(l, 0, sizeof(l));
    memset(r, 0, sizeof(r));
    for(int i = n; i >= 1; i--)
    {
        for(int j = 1; j <= m + 2; j++)
            scanf("%c", building[i] + j);
        getchar();
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m + 2; j++)
        {
            if(building[i][j] == '1')
            {
                r[i] = j;
                if(l[i] == 0)l[i] = j;
            }
        }
    }
}

void out()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m + 2; j++)
            printf("%c", building[i][j]);
        printf("\n");
    }
}

bool isempty(int row)
{
    for(int j = 1; j <= m + 2; j++)
        if(building[row][j] == '1')return false;
    return true;
}

bool check()
{
    for(int i = n; i > 1; i--)
        if(!isempty(i))return false;
    if(isempty(1))return true;
    return false;
}

int findtop()
{
    int top = -1;
    for(int i = n; i >= 1; i--)
        if(isempty(i))top = i;
        else return top;
    return top;
}

int main()
{
    while(~scanf("%d%d\n", &n, &m))
    {
        int dp[30][2] = {0};
        input();
        if(r[1] == 0)dp[1][0] = 0;
        else
            dp[1][0] = 2 * (r[1] - 1);
        dp[1][1] = m + 1;
        for(int i = 2; i < n; i++)
        {
            if(r[i] == 0)
            {
                dp[i][0] = min(dp[i-1][0], dp[i-1][1]+m+1) + 1;
                dp[i][1] = min(dp[i-1][1], dp[i-1][0]+m+1) + 1;
            }
            else
            {
                dp[i][0] = min(dp[i-1][0]+2*(r[i]-1), dp[i-1][1]+m+1) + 1;
                dp[i][1] = min(dp[i-1][1]+2*(m+2-l[i]), dp[i-1][0]+m+1) + 1;
            }
        }
        int ans = 0;
        if(r[n] == 0)
        {
            ans = min(dp[n-1][0], dp[n-1][1]);
            if(r[n-1] != 0)
                if(dp[n-1][0] < dp[n-1][1])ans -= r[n-1]-1;
                else ans -= m+2-l[n-1];
        }
        else
        {
            ans = min(dp[n-1][0]+r[n]-1, dp[n-1][1]+m+2-l[n]) + 1;
            if(n == 1)ans--;
        }

/*
        printf("\n");

        printf("\nl\\r:\n");
        for(int i = 1; i <= n; i++)
            printf("l[%d] = %d,\tr[%d] = %d\n", i, l[i], i, r[i]);
        printf("\n");

        printf("\ndp:\n");
        for(int i = 1; i <= n; i++)
            printf("dp[%d][0] = %d,\tdp[%d][1] = %d\n", i, dp[i][0], i, dp[i][1]);
        printf("\n");
*/
        if(findtop() == 2)ans = r[1] - 1;
        if(findtop() == 1)ans = 0;
        printf("%d\n", ans);
    }
    return 0;
}
