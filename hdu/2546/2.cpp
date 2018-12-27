#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, m;
int price[maxn];
int dp[maxn];

int main(){
    while(~scanf("%d", &n) && n){
        memset(price, 0, sizeof(price));
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; ++ i)
            scanf("%d", price + i);
        scanf("%d", &m);
        sort(price + 1, price + n + 1);
        dp[0] = m;
        for(int i = 1; i <= n; ++ i){
            dp[i] = min(dp[i-1] - price[i], );
        }
    }
    return 0;
}