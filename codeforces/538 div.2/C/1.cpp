#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const size_t maxn = 10010;
const ll inf = 0x3f3f3f3f3f3f3f3f;

ll n, b;
pli rec[maxn];

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
        for(ll i = 2; i <= top; ++ i){
            ll curp = i;
            int cnt = 0;
            while(b % i == 0){
            // printf("b = %lld\n", b);
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
