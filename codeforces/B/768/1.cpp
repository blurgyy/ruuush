#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, l, r;

ll ret_len(ll n){
    ll ret = 1;
    while(n){
        n /= 2;
        ret *= 2;
    }
    return ret - 1;
}

ll counter(ll len, ll pos, ll n){
    if(n < 2)return n;
    if(pos * 2 == len + 1)return n % 2;
    n >>= 1;
    len >>= 1;
    if(pos > len + 1)
        pos -= len + 1;
    return counter(len, pos, n);
}

int main(){
    while(~scanf("%I64d%I64d%I64d", &n, &l, &r)){
        //printf("%I64d\n", ret_len(n));
        ll len = ret_len(n);
        ll ans = 0;
        for(ll i = l; i <= r; ++ i){
            ans += counter(len, i, n);
            //printf("ans = %d\n", ans);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}