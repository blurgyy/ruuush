#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
//const int maxn = 1000010;
const int mod = 1000000007;
const int inv2 = mod + 1 >> 1;

int T;
ll n;

ll calc(ll fx){
    ll x = 1;
    while(fx){
        x += fx;
        fx >>= 1;
    }
    return x;
}

ll bs(ll e, ll left, ll right){
    if(left >= right)return right;
    ll mid = left + right >> 1;
    //printf("e = %lld, left = %lld, right = %lld, ", e, left, right);
    ll x = calc(mid);
    //printf("x = %lld\n", x);
    if(e <= x)return bs(e, left, mid);
    return bs(e, mid + 1, right);
}

int main(){

    scanf("%d", &T);
    while(T --){
        scanf("%lld", &n);
        if(n == 1){
            printf("1\n");
            continue;
        }
        //printf("f(%lld) = %lld\n", calc(n), n);
        ll fn = bs(n, 1, n);
        //printf("f(%lld) = %lld\n", n, fn);
        if(fn % 2 == 0)fn --;
        ll top = calc(fn);
        ll ans = 1;
        for(ll d = 1; d <= fn; d <<= 1){
            ll times = (fn / d) % mod;
            ll a_n = (fn - fn % d) % mod;
            ans += (times * ((d + a_n) % mod) % mod) * inv2 % mod;
            ans %= mod;
            //printf("ans = %lld, d = %lld, a_n = %lld\n", ans, d, a_n);
            //ll times = fn / d;
            //if(times % 2 == 0)times >>= 1;
            //ll a_n = d + fn - fn % d;
            //printf("d = %lld, a_n = %lld, ", d, a_n - d);
            //if(a_n % 2 == 0)a_n >>= 1;
            //ans += (times % mod)* (a_n % mod) % mod;
            //ans %= mod;
            //printf("ans = %lld\n", ans);
        }
        ans = (ans + ((n - top) % mod) * ((fn + 1) % mod) % mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}

///46546518453
///4894894651654168

/**

271631
271632

*/