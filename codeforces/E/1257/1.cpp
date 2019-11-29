#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int a[maxn];
int k[3];
int dp[3][maxn];

int main(){
    while(~scanf("%d%d%d", k+0, k+1, k+2)){
        int tot = k[0] + k[1] + k[2];
        for(int i = 0, x; i < 3; ++ i){
            while(k[i] --){
                scanf("%d", &x);
                a[x] = i;
            }
        }
        dp[0][0] = dp[1][0] = dp[2][0] = 0;
        for(int i = 1; i <= tot; ++ i){
            dp[0][i] = dp[0][i-1] + (a[i] != 0);
            dp[1][i] = min(dp[0][i-1], dp[1][i-1]) + (a[i] != 1);
            dp[2][i] = min(dp[0][i-1], min(dp[1][i-1], dp[2][i-1])) + (a[i] != 2);
            // printf("%d %d %d\n", dp[0][i], dp[1][i], dp[2][i]);
        }
        printf("%d\n", min(dp[0][tot], min(dp[1][tot], dp[2][tot])));
    }
    return 0;
}
