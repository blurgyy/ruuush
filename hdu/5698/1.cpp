#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;
const int mod = 1e9 + 7;

ll n, m;

ll C(int bot, int top){
    if(top > bot>>1)top = bot - top;
    int stp = 1;
    ll ret = 1;
    while(stp <= top){
        ret *= bot --;
        ret /= stp++;
        ret %= mod;
    }
    return ret;
}

int main(){
    while(scanf("%lld%lld", &n, &m)){
        int bot = n + m - 4, top = min(n, m) - 2;
        printf("%lld\n", C(bot, top));
    }
    return 0;
}