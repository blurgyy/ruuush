#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1510;
const int inf = 0x3f3f3f3f;

int T, n;
int a[maxn], pref[maxn], sum[maxn];
int dp[maxn];

void init(){
    memset(a, 0, sizeof(a));
    memset(pref, 0, sizeof(pref));
    memset(sum, 0, sizeof(sum));
    memset(dp, 0x3f, sizeof(dp));
}

int main(){
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            pref[i] = pref[i-1] + a[i];
            sum[i] = sum[i-1] + a[i] * (n - i);
        }
/*
        for(int i = 1; i <= n; ++ i){
            printf("%d ", pref[i]);
        }
        printf("\n");
        for(int i = 1; i <= n; ++ i){
            printf("%d ", sum[i]);
        }
        printf("\n");
*/
        dp[0] = 0;
        dp[1] = pref[n] - pref[1];
        for(int i = 2; i <= n; ++ i){
            for(int j = 0; j < i; ++ j){
                int curans = dp[j] + (sum[i] - sum[j] - (pref[i] - pref[j]) * (n - i)) + pref[n] - pref[i];
                dp[i] = min(dp[i], curans);
            }
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}