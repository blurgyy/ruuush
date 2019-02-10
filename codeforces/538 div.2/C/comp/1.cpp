#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const size_t maxn = 10010;
const ll inf = 0x3f3f3f3f3f3f3f3f;

ll n, b;
pli rec[maxn];

ll quick_mod(ll a, ll b, ll MOD)
{
    ll ans;
    
    ans = 1;
    while(b){
        if(b & 1){
            ans = (ans * a) % MOD;
        }
        b >>= 1;
        a = a * a % MOD;
    }

    return ans % MOD;
}

bool rqui_prime(ll x){ //x不能超int   /// shizhushuyes = true 
    srand(time(0));
    int n = log(x)+7;
    if(quick_mod(7,x-1,x) != 1) {
        return false;
    }
    for(int i = 0; i < n; i++) {
        long long k = rand()%10000+7;
        if((k%x)&&(quick_mod(k,x-1,x)!=1)) { /// 快速幂 
            return false;
        }
    }
    return true;
}

ll count(ll top, ll p){
    ll ret = 0;
    top /= p;
    while(top){
        ret += top;
        top /= p;
    }
    return ret;
}

int main(){
    while(~scanf("%lld%lld", &n, &b)){
        // printf("%lld\n", count(6, 3));
        int p = 0;
        int top = sqrt(b) + 1;
        for(ll i = 2; b > 1 && rqui_prime(b) == false; ++ i){
            ll curp = i;
            int cnt = 0;
            while(b % i == 0){
                cnt ++;
                b /= i;
            }
            if(cnt){
                rec[p++] = make_pair(curp, cnt);
                // printf("%lld %d\n", curp, cnt);
            }
        }
        if(b > 1) rec[p++] = make_pair(b, 1);
        ll ans = inf;
        for(int i = 0; i < p; ++ i){
            ll curp = rec[i].first;
            ans = min(ans, count(n, curp) / rec[i].second);
        }
        if(ans == inf) ans = 0;
        printf("%lld\n", ans);
    }
    return 0;
}