#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, l, r;
ll len;

ll length(ll x){
    ll pos = 1;
    while(x){
        x >>= 1;
        pos <<= 1;
    }
    return pos - 1;
}

int contrib(ll pos, ll left = 1, ll right = len+1){
    ll curpos = left + right >> 1;
    int ret = n % 2;
    ll nn = n / 2;
    while(curpos != pos){
        if(pos > curpos){
            left = curpos;
        }
        else {
            right = curpos;
        }
        curpos = left + right >> 1;
        ret = nn % 2;
        nn /= 2;
    }
    return ret;
}

int main(){
    // while(~scanf("%lld%lld%lld", &n, &l, &r)){
    scanf("%lld%lld%lld", &n, &l, &r);{
        len = length(n);
        int ans = 0;
        for(ll i = l; i <= r; ++ i){
            if(i & 1) ans ++;
            else ans += contrib(i);
        }
        if(n == 0) ans = 0;
        printf("%d\n", ans);
    }
    return 0;
}