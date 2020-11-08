#include<bits/stdc++.h>

using namespace std;

int n,k,t;
char a[1010],ch;
int dp[1010][20],ans;

int main(){
    scanf("%d%d%d",&n,&k,&t);
    scanf("%c",&ch);
    for (int i=1;i<=n+1;i++){
        if (i!=n+1) scanf("%c",&a[i]);
        for (int j=1;j<=k+(i==n+1?1:0);j++){
            dp[i][j]=2000;
        }
    }
    ans=n;
    for (int i=1;i<=n+1;i++){
        if (a[i]!='0'){
            dp[i][1]=i-1;
            for (int j=2;j<=k+(i==n+1?1:0);j++){
                for (int x=1;x<i;x++){
                    dp[i][j]=min(dp[i][j],dp[x][j-1]+max(0,i-x-t));
                }
                if (i==n+1) ans=min(ans,dp[i][j]);
                //printf("%d %d %d\n",i,j,dp[i][j]);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
