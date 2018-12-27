#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;

ll n, k;
ll ans[5];

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
        ans[1] = 1;
        ans[2] = ans[1] + A(n, 2) - C(n, 2);
        ans[3] = ans[2] + A(n, 3) - C(n, 3) * (1 + C(3, 1));
        ans[4] = ans[3] + A(n, 4) - C(n, 4) * (1 + C(4, 3) + C(4, 2) + C(4, 1));
        printf("%I64d\n", ans[k]);
    }
    return 0;
}