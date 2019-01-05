#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const int mod = 1e9 + 7;
const size_t maxn = 100010;

ll n;
int k;
ll fac[maxn];
int tot;
map<ll, int> pfac;
ll prec[1010];
int ptot;

ll inv(int n){
    if(n == 1) return 1;
    return 1ll * (mod - mod / n) * inv(mod % n) % mod;
}

int main(){
    // ll x = 1ll * (9 + 6 + 9 + 6) * inv(16) % mod;
    // printf("%lld, %lld\n", x, 1ll * 15 * inv(8) % mod);
    while(~scanf("%lld%d", &n, &k)){
        pfac.clear();
        ptot = 0;
        ll top = (ll)sqrt(n) + 1;
        int p = 0;
        for(ll i = 1; i <= top; ++ i){
            if(n % i == 0){
                fac[p++] = i;
                fac[p++] = n / i;
            }
        }
        sort(fac, fac + p);
        tot = unique(fac, fac + p) - fac;

        for(ll i = 2, x = 0, tmp = n; i <= top; ++ i, x = 0){
            while(tmp % i == 0){
                x ++;
                tmp /= i;
            }
            if(x) {
                pfac[i] = x;
                prec[ptot++] = i;
            }
        }
        map<ll, int> tmp;
        map<ll, int> fcnt;  ///fac cnt for each fac[i]
        for(int i = 0; i < tot-1; ++ i, tmp.clear()){
            if(fcnt[fac[i]] != 0) continue;
            printf("[%lld]:\n", fac[i]);
            for(ll j = 0, x = 0, temp = fac[i]; j < ptot; ++ j, x = 0){
                while(temp % prec[j] == 0){
                    x ++;
                    temp /= prec[j];
                }
                if(x) {
                    tmp[prec[j]] = x;
                    printf("[%lld] = %d\n", prec[j], x);
                }
            }
            fcnt[fac[i]] = fcnt[n/fac[i]] = 1;
            for(int i = 0; i < ptot; ++ i){
                fcnt[fac[i]] *= tmp[prec[i]] + 1;
                fcnt[n/fac[i]] *= pfac[prec[i]] - tmp[prec[i]] + 1;
            }
        }
        for(auto i = fcnt.begin(); i != fcnt.end(); ++ i){
            printf("%lld %d\n", i->first, i->second);
        }

        // int anssss = 1;
        // for(auto i = pfac.begin(); i != pfac.end(); ++ i){
        //     anssss *= i->second + 1;
        // }
        // printf("anssss = %d\n", anssss);

    }
    return 0;
}