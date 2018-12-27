#include <cstdio>
typedef long long ll;
const int inf = 0x3f3f3f3f;
const ll mod = 998244353;

ll inv(ll x){
    if(x == 1)return 1;
    return (mod - mod / x) * inv(mod % x) % mod;
}

int main(){
    ll x;
    while(~scanf("%lld", &x)){
        printf("inv(%lld) = %lld\n", x, inv(x));
    }
    return 0;
}