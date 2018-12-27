#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;

int n, m;
char building[20][110];
int l[150], r[150];

void input()
{
    memset(l, -1, sizeof(l));
    memset(r, -1, sizeof(r));
    for(int i = n; i >= 1; i--)
    {
        for(int j = 1; j <= m + 2; j++)
            scanf("%c", building[i] + j);
        getchar();
    }
    for(int i = 1; i <= n; i++)
    {
        bool flag = false;
        for(int j = 1; j <= m + 2; j++)
        {
            if(building[i][j] == '1' && building[i][j+1] == '0')r[i] = j;
            if(flag)continue;
            if(building[i][j] == '1')
            {
                flag = true;
                l[i] = j;
            }
        }
    }
}

bool checkempty(int row)
{
    for(int j = 1; j <= m + 2; j++)
        if(building[row][j] == '1')return false;
    return true;
}

int findtop()
{
    for(int i = n; i >= 1; i--)
    {
        if(checkempty(i))continue;
        return i;
    }
}

int main()
{
    while(~scanf("%d%d\n", &n, &m))
    {
        int dp[maxn][2] = {0};
        dp[1][0] = 0;
        dp[1][1] = m+1;
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        input();
        int top = findtop();
        for(int i = 2; i <= top; i++)
        {
            if(checkempty(i))
            {
                dp[i][0] = min(dp[i-1][0] + 1, dp[i-1][1] + 1 + m + 1);
                dp[i][1] = min(dp[i-1][0] + 1 + m + 1, dp[i-1][1] + 1);
            }
            else
            {
                dp[i][0] = min(dp[i-1][0] + r[i-1]*2 + 1, dp[i-1][1] + m + 2);
                dp[i][1] = min(dp[i-1][0] + m + 2, dp[i-1][1] + (m+1-l[i-1]) * 2 + 1);
            }
        }
        int ans;
        ans = min(dp[top][0] + r[top], dp[n-top+1][1] + (m+1-l[top]));
        printf("%d\n", ans);
    }
}
/**

#include<bits/stdc++.h>
using namespace std;

char a[20][105];
int l[20],r[20];
int dp[20][2];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    memset(a,'0',sizeof(a));
    memset(l,0,sizeof(l));
    memset(r,0,sizeof(r));
    memset(dp,0,sizeof(0));
    cin>>n>>m;
    for(int i=n;i>=1;i--){
        for(int j=0;j<=m+1;j++){
            cin>>a[i][j];
            if(a[i][j]=='1'){
                r[i]=j;
                if(l[i]==0){
                    l[i]=j;
                }
            }
        }
    }
    int high=n;
    for(int i=n;i>0;i--){
        if(l[i]==0&&r[i]==0){
            high--;
        }
        else break;
    }
    dp[1][0]=0;
    dp[1][1]=m+1;
    for(int i=2;i<=high;i++){
        if(l[i-1]==0&&r[i-1]==0){
            dp[i][0]=min(dp[i-1][0],dp[i-1][1]+m+1)+1;
            dp[i][1]=min(dp[i-1][1],dp[i-1][0]+m+1)+1;
        }
        else {
            dp[i][0]=min(dp[i-1][0]+r[i-1]*2,dp[i-1][1]+m+1)+1;
            dp[i][1]=min(dp[i-1][1]+(m+1-l[i-1])*2,dp[i-1][0]+m+1)+1;
        }
    }
    int result;
    result=min(dp[high][0]+r[high],dp[high][1]+(m+1-l[high]));
    cout<<result<<endl;


return 0;
}
*/
