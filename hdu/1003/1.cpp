#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int T, n, ans;
int a[maxn] = {0};
int dp[maxn];

void out(){
    printf("array a:\n");
    for(int i = 0; i <= n; ++ i)
        printf("%d ", a[i]);
    printf("\n");
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        memset(dp, 0, sizeof(dp));
        ans = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            printf("%d ", a[i]);
            dp[i] = max(dp[i-1] + a[i], a[i]);
        }
        int pos;
        for(int i = 1; i <= n; ++ i){
            if(ans <= dp[i]){
                pos = i;
                ans = dp[i];
            }
        }
        printf("%d ", ans);
        int sum = 0;
        for(int i = pos; i > 0; -- i){
            sum += a[i];
            if(sum == ans){
                printf("sum = %d, %d\n", sum, a[i]);
                printf("%d %d\n", i, pos);
                break;
            }
        }
    }
    return 0;
}