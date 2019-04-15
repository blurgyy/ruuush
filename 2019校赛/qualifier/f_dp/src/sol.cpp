#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2010;

int T, n;
ll w[maxn];
ll dp[maxn][maxn];

int main(){
	while(~scanf("%d", &T)){
		while(T --){
			scanf("%d", &n);
			for(int i = 1; i <= n; ++ i){
				scanf("%lld", w + i);
			}
			// memset(dp, 0, sizeof(dp));
			dp[0][0] = 0;
			for(int i = 1; i <= n; ++ i){
				dp[i][0] = dp[i-1][0] + i * w[i];
				dp[0][i] = dp[0][i-1] + i * w[n-i+1];
			}
			ll ans = 0;
			for(int i = 1; i <= n; ++ i){
				for(int j = 1; j <= n-i; ++ j){
					dp[i][j] = max(dp[i-1][j] + 1ll * (i+j) * w[i], dp[i][j-1] + 1ll * (i+j) * w[n-j+1]);
					// printf("dp[%d][%d] = %lld\n", i, j, dp[i][j]);
					ans = max(ans, dp[i][j]);
				}
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
