#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;
const int mod = 998244353;

int n, k;
ll dp[maxn][maxn<<1][4];

ll sumij(int i, int j){
    ll ret;
    ret = 1LL * dp[i][j][0] + dp[i][j][1] + dp[i][j][2] + dp[i][j][3];
    return ret % mod;
}

int main(){
    while(~scanf("%d%d", &n, &k)){
        memset(dp, 0, sizeof(dp));
        dp[1][1][0] = 1;
        dp[1][2][1] = 1;
        dp[1][2][2] = 1;
        dp[1][1][3] = 1;
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= k; ++ j){
                dp[i][j][0] = (dp[i][j][0] + (i<1?0:dp[i-1][j][0]) + (i<1?0:dp[i-1][j][1]) + (i<1?0:dp[i-1][j][2]) + (i<1||j<1?0:dp[i-1][j-1][3])) % mod;
                dp[i][j][1] = (dp[i][j][1] + (i<1||j<1?0:dp[i-1][j-1][0]) + (i<1?0:dp[i-1][j][1]) + (i<1||j<2?0:dp[i-1][j-2][2]) + (i<1||j<1?0:dp[i-1][j-1][3])) % mod;
                dp[i][j][2] = (dp[i][j][2] + (i<1||j<1?0:dp[i-1][j-1][0]) + (i<1||j<2?0:dp[i-1][j-2][1]) + (i<1?0:dp[i-1][j][2]) + (i<1||j<1?0:dp[i-1][j-1][3])) % mod;
                dp[i][j][3] = (dp[i][j][3] + (i<1||j<1?0:dp[i-1][j-1][0]) + (i<1?0:dp[i-1][j][1]) + (i<1?0:dp[i-1][j][2]) + (i<1?0:dp[i-1][j][3])) % mod;
            }
        }
        ll ans = sumij(n, k);
        printf("%I64d\n", ans);
    }
    return 0;
}