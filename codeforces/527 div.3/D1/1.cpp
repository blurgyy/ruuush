#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;

int n;
int a[maxn];
int x[maxn];
int dp[maxn];

int main(){
    while(~scanf("%d", &n)){
        ll sum = 0;
        ll maxx = -1;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            sum += a[i];
            maxx = max(maxx, 1ll*a[i]);
        }
        if(n&1 == 0 && sum & 1){
            printf("No\n");
            continue;
        }
        ll tot = 1ll * n * maxx;
        if(tot-sum & 1) {
            maxx ++;
            tot += n;
        }
        maxx += 2;
        tot += n + n;
        for(int i = 1; i <= n; ++ i){
            x[i] = maxx - a[i];
            // printf("x[%d] = %d\n", i, x[i]);
        }
        // printf("tot = %I64d\n", tot);
        memset(dp, 0, sizeof(dp));  /// all not started from bottom (false)
        for(int i = 1; i <= n; ++ i){
            if(x[i] & 1){
                // x[i] = !x[i];
                // x[i+1] = !x[i+1];
                
                if(dp[i] == 0 || dp[i] == 2){
                    dp[i] = 1;
                    dp[i+1] = 1;
                }
                else if(dp[i] == 1){
                    dp[i+1] = 2;
                }
                x[i] --;
                x[i+1] --;
            }
            else {
                if(i < n){
                    dp[i] = 1;
                }
                else {
                    dp[i] = max(dp[i], 1);
                }
            }
        }

        // for(int i = 1; i <= n; ++ i){
        //     printf("%d%c", x[i], " \n"[i==n]);
        // }
        // for(int i = 1; i <= n; ++ i){
        //     printf("%d%c", dp[i], " \n"[i==n]);
        // }
        bool ans = true;
        for(int i = 1; i <= n; ++ i){
            if(dp[i] != 1) {
                ans = false;
                break;
            }
        }
        puts(ans ? "YES" : "NO");
    }
    return 0;
}