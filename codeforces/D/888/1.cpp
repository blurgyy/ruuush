#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;

ll n, k;
ll dp[maxn];

ll A(ll bot, ll top){
    ll ret = 1;
    for(ll i = 0; i < top; ++ i)
        ret *= bot - i;
    return ret;
}

ll C(ll bot, ll top){
    ll up = 1, down = 1;
    for(ll i = 0; i < top; ++ i)
        up *= bot - i;
    for(ll i = 2; i <= top; ++ i)
        down *= i;
    return up / down;
}

int main(){
    while(~scanf("%I64d%I64d", &n, &k)){
        dp[0] = dp[1] = 1;
        for(ll i = 2; i <= k; ++ i){
            dp[i] = A(n, i);
            for(int j = i; j > 0; -- j){
                dp[i] -= C(n, j);
            }
            //printf("C(%I64d, %I64d) = %I64d\n", n, i, C(n, i));
        }
        printf("%I64d\n", dp[k]);
    }
    return 0;
}