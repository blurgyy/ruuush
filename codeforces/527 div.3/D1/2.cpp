#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;

int n;
int a[maxn];
ll sum, maxx;
int x[maxn];
int dp[maxn];

int main(){
    while(~scanf("%d", &n)){
        sum = maxx = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            sum += a[i];
            maxx = max(maxx, 1ll * a[i]);
        }
        maxx += 2;
        if(n % 2 == 0 && sum % 2 == 1){
            puts("NO\n");
            continue;
        }
        ll tot = maxx * n;
        if((tot - sum) % 2 == 1){
            tot = (++maxx) * n;
        }
        for(int i = 1; i <= n; ++ i){
            x[i] = maxx - a[i];
            // printf("%d%c", x[i], " \n"[i==n]);
        }
        memset(dp, 0, sizeof(dp));
        bool ans = true;
        for(int i = 1; i <= n; ++ i){
            if(x[i] & 1){
                x[i] --;
                x[i+1] --;
                if(dp[i] == 0){
                    dp[i] = 1;
                    dp[i+1] = 1;
                }
                else if(dp[i] == 1){
                    dp[i] = 3;
                    dp[i+1] = 2;
                }
                else if(dp[i] == 2){
                    dp[i] = 3;
                    dp[i+1] = 1;
                }
                else {
                    while(true);
                }
            }
            else {
                if(dp[i] == 2){
                    ans = false;
                    break;
                }
            }
        }
        puts(ans ? "YES" : "NO");
    }
    return 0;
}