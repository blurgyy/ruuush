#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int mod = 998244353;

int n;
ll fac[maxn];
ll inv[maxn];

void init(){
    fac[0] = 1;
    inv[1] = 1;
    for(int i = 1; i < maxn; ++ i)
        fac[i] = (1ll * fac[i-1] * i) % mod;
    for(int i = 2; i < maxn; ++ i)
        inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    for(int i = 2; i < maxn; ++ i)
        inv[i] = (inv[i-1] * inv[i]) % mod;
}

int main(){
    init();
    while(~scanf("%d", &n)){
        ll ans = 0;
        for(int i = 2; i < n; ++ i){
            // ans = (ans + 1ll * (n-i) * fac[n-1] % mod * inv[i] % mod * n % mod) % mod;
            ans = (ans + 1ll * (n-i) * fac[n-1] % mod * inv[i] % mod *(1ll * i - 1) % mod) % mod;
        }
        ans = ((ans * n) % mod + fac[n]) % mod;
        printf("%I64d\n", ans);
    }
    return 0;
}