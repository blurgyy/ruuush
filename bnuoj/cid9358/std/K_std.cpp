#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int t,n,m;
int a[1010],b[110];
int dp[2][110][110][4];
int main()
{
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++)
    {
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=1; i<=n; i++) scanf("%d",&a[i]);
        for(int i=1; i<=m; i++) scanf("%d",&b[i]);
        sort(b+1,b+m+1);
        int f=0;
        for(int p=0; p<=n; p++)
        {
            f^=1;
            for(int i=1; i<=m+1; i++)
            {
                for(int len=m-i+1; len>=0; len--)
                {
                    int j=i+len-1;
                    if(p)
                    {
                        dp[f][i][j][0]=max(max(dp[f^1][i][j][0],dp[f^1][i][j][1]),max(dp[f^1][i][j][2],dp[f^1][i][j][3]));
                        dp[f][i][j][1]=max(dp[f^1][i][j][0],dp[f^1][i][j][2])+a[p];
                    }
                    if(i>1) dp[f][i][j][2]=max(max(dp[f][i-1][j][0],dp[f][i-1][j][1]),max(dp[f][i-1][j][2],dp[f][i-1][j][3]));
                    if(j<m) dp[f][i][j][3]=max(dp[f][i][j+1][0],dp[f][i][j+1][2])+b[j+1];
                }
            }
        }
        int ans=0;
        for(int i=1; i<=m+1; i++)
        {
            int res=max(max(dp[f][i][i-1][0],dp[f][i][i-1][1]),max(dp[f][i][i-1][2],dp[f][i][i-1][3]));
            ans=max(ans,res);
        }
        printf("%d\n",ans);
    }
    return 0;
}
