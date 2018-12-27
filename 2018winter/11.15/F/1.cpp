/// F
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2000010;
const int mod = 1e6 + 3;

ll n, a, b, c;
ll fac[maxn], inv[maxn];
ll ga[maxn], gb[maxn];
ll powa[maxn], powb[maxn];
ll dp[maxn];

ll C(ll a, ll b){
    return fac[a] * inv[b] % mod * inv[a - b] % mod;
}

ll Get_inv(ll n){
    if(!n){
        return 1;
    }
	if(n == 1)return 1;
	return (mod - mod / n) * Get_inv(mod % n) % mod;
}
void init(){
    inv[0] = inv[1] = fac[0] = 1;
    powa[0] = powb[0] = 1;
    for(int i = 1; i < maxn; ++ i) fac[i] = (fac[i-1] * i) % mod;
    for(int i = 2; i < maxn; ++ i) inv[i] = (mod - mod / i) * inv[mod%i] % mod;
    for(int i = 2; i < maxn; ++ i) inv[i] = inv[i - 1] * inv[i] % mod;
    for(int i = 1; i < maxn; ++ i) powa[i] = powa[i-1] * a % mod, powb[i] = powb[i-1] * b % mod;
    ga[1] = 1, gb[1] = 1;
    if(!a){
        memset(ga, 0, sizeof(ga));
    }
    if(a == 1){
        for(int i = 2; i <= n; i ++){
            ga[i] = C(2 * i - 1, i - 1);
        }
    }
    else{
        for(int i = 2; i <= n; ++ i){
//        ga[i] = (ga[i-1] + C(2*i-2, i-1) * powa[i-1] % mod + C(2*i-1, i-1) * powa[i] % mod) % mod * inv[];
//        gb[i] = (gb[i-1] + C(2*i-2, i-2) * powb[i-1] % mod + C(2*i-1, i-1) * powb[i] % mod) % mod;

            ga[i] = ((C(2*i-1, i-1) * powa[i] % mod - (ga[i-1] + C(2*i-2, i-1) * powa[i-1] % mod) % mod + mod) % mod ) * Get_inv(a - 1) % mod;
            // gb[i] = ((C(2*i-1, i-1) * powb[i] % mod - (gb[i-1] + C(2*i-2, i-1) * powb[i-1] % mod) % mod + mod) % mod ) * Get_inv(b - 1) % mod;
            // cout << ga[i] << ' ' << gb[i] << endl;
        }
    }
    if(!b){
        memset(gb, 0, sizeof(gb));
    }
    if(b == 1){
        for(int i = 2; i <= n; i ++){
            gb[i] = C(2 * i - 1, i - 1);
        }
    }
    else{
        for(int i = 2; i <= n; ++ i){
//        ga[i] = (ga[i-1] + C(2*i-2, i-1) * powa[i-1] % mod + C(2*i-1, i-1) * powa[i] % mod) % mod * inv[];
//        gb[i] = (gb[i-1] + C(2*i-2, i-2) * powb[i-1] % mod + C(2*i-1, i-1) * powb[i] % mod) % mod;

            // ga[i] = ((C(2*i-1, i-1) * powa[i] % mod - (ga[i-1] + C(2*i-2, i-1) * powa[i-1] % mod) % mod + mod) % mod ) * Get_inv(a - 1) % mod;
            gb[i] = ((C(2*i-1, i-1) * powb[i] % mod - (gb[i-1] + C(2*i-2, i-1) * powb[i-1] % mod) % mod + mod) % mod ) * Get_inv(b - 1) % mod;
            // cout << ga[i] << ' ' << gb[i] << endl;
        }
    }
}

int main(){
    int t;
    while(~scanf("%lld%lld%lld%lld", &n, &a, &b, &c)){
        init();
//        while(true){
//            scanf("%lld%lld", &a, &b);
//            printf("%lld\n", C(a, b));
//        }
        dp[0] = 1;

        for(int i = 1; i <= n; ++ i){
            dp[i] = (dp[i-1] + powa[i] * gb[i] % mod + powb[i] * ga[i] % mod + (C(2*i, i) * powa[i]) % mod * powb[i] % mod) % mod;
            // cout << dp[i] << endl;
        }
        ll add = 0;
        scanf("%d", &t);
        for(int i = 2; i <= n; ++ i){
            ll x;
            scanf("%lld", &x);
            add = (add + a * x % mod * (powa[n-2] * powb[n-i] % mod * C(2*n-i-2, n-2) % mod) % mod) % mod;
        }
        scanf("%d", &t);
        for(int i = 2; i <= n; ++ i){
            ll x;
            scanf("%lld", &x);
            add = (add + b * x % mod * (powb[n-2] * powa[n-i] % mod * C(2*n-i-2, n-2) % mod) % mod) % mod;
        }
        //cout << add << "qqq" << endl;
        ll ans = (add + dp[n-2] * c % mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
