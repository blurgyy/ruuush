#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n, a[maxn], dp[maxn][3];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; ++ i)
            scanf("%d", a + i);
        for(int i = 1; i < maxn; ++ i)
            dp[i][0] = dp[i][1] = dp[i][2] = maxn;
        memset(dp[0], 0, sizeof(dp[0]));
        for(int i = 1; i <= n; ++ i){
            if(a[i] == 0){
                dp[i][0] = min(dp[i-1][0], min(dp[i-1][1], dp[i-1][2])) + 1;
            }
            else if(a[i] == 1){
                dp[i][0] = min(dp[i-1][0], min(dp[i-1][1], dp[i-1][2])) + 1;
                dp[i][1] = min(dp[i-1][0], dp[i-1][2]);
            }
            else if(a[i] == 2){
                dp[i][0] = min(dp[i-1][0], min(dp[i-1][1], dp[i-1][2])) + 1;
                dp[i][2] = min(dp[i-1][0], dp[i-1][1]);
            }
            else if(a[i] == 3){
                dp[i][0] = min(dp[i-1][0], min(dp[i-1][1], dp[i-1][2])) + 1;
                dp[i][1] = min(dp[i-1][0], dp[i-1][2]);
                dp[i][2] = min(dp[i-1][0], dp[i-1][1]);
            }
        }
        int ans = maxn;
        for(int i = 0; i < 3; ++ i)
            ans = min(ans, dp[n][i]);
        printf("%d\n", ans);
    }
    return 0;
}