#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 262144;
const int mod = 998244353;

ll n;
ll pow2[maxn];
ll ans[maxn];

ll ma[maxn];
ll mb[maxn];
ll quickmod(ll a, ll b, ll mod)
{
    ll ans;

    ans = 1;
    while(b){
        if(b & 1){
            ans = (ans * a) % mod;
        }
        b >>= 1;
        a = a * a % mod;
    }

    return ans % mod;
}

ll C(int a, int b)
{
    if(b < 0 || b > a){
        return 0;
    }
    if(b == 0 || a == b){
        return 1;
    }
    return ma[a] * mb[a - b] % mod * mb[b] % mod;
}

void Ini()
{
    ma[0] = 1;
    mb[0] = quickmod(ma[0], mod - 2, mod);
    ma[1] = 1;
    mb[1] = quickmod(ma[1], mod - 2, mod);
    for(int i = 2; i <= maxn; i ++){
        ma[i] = (ma[i - 1] * i) % mod;
        mb[i] = quickmod(ma[i], mod - 2, mod);
    }
}



int main(){
    //freopen("in.in", "w", stdout);
    //for(int i = 1; i <= 2048; ++ i)
    //    printf("%d\n", i);
    //return 0;
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    Ini();
    pow2[0] = 1;
    // cout << C(3, 3) << endl;
    for(int i = 1; i < maxn; ++ i){
        pow2[i] = pow2[i-1] * 2 % mod;
        // cout << pow2[i] << endl;
    }
    while(~scanf("%lld", &n)){
        if(n == 1){
            printf("1\n");
        }
        else{
            n --;
            ans[n] = 0;
            //for(int i = 2; i <= n; ++ i){
            //    ans[i] = (ans[i-1] + calc(i-1)) % mod;
            //}
            //printf("%lld\n", ans[n]);
            for(int i = 1; i <= n; ++ i){
                // cout << "t = " << C(n, 1ll * i) << endl;
                ans[n] = (ans[n] + (pow2[i] * C(n, i) % mod * C(n, i-1)) % mod) % mod;
                // cout << ans[n] << endl;
            }
            printf("%lld\n", ans[n] * quickmod(n, mod - 2, mod) % mod);
        }
    }
}

/**

780401176

*/