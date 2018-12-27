#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1000010;

int T;
ll n;

ll calc(ll x){
    ll ret = 0;
    while(x){
        ret += x;
        x >>= 1;
    }
    return ret;
}

ll bs(int e, ll left, ll right){
    if(left >= right)return right;
    ll mid = (right - left >> 1) + left;
    ll index = calc(mid);
    //printf("index = %d\n", index);
    if(e <= index)return bs(e, left, mid);
    return bs(e, mid + 1, right);
}

int main(){
    //freopen("in.in", "w", stdout);
    //printf("%d\n", maxn - 1);
    //for(int i = 1; i < maxn; ++ i){
    //    printf("%d\n", i);
    //}
    //return 0;
    //freopen("in.in", "r", stdin);
    //freopen("tmp.out", "w", stdout);
    scanf("%d", &T);
    while(T --){
        scanf("%lld", &n);
        if(n == 1){
            printf("1\n");
            continue;
        }
        ll fn = bs(n - 1, 1, n);
        if(!(fn & 1)){
            fn -= 1;
        }
        ll ans = 1;
        for(ll d = 1; d <= fn; d <<= 1){
            //printf("d = %lld\n", d);
            ans = (ans + ((fn / d) * (d + fn - fn % d)) / (2)) % mod;
            //printf("adding %lld\n", ((fn / d) * (d + fn - fn % d)) / (2));
        }
        ll top = 1, tmp = fn ++;
        while(tmp){
            top += tmp;
            tmp >>= 1;
        }
        ans = (ans + (n - top) * fn) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}