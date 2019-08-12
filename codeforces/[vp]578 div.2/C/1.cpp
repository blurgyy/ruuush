#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
int q;
ll sx, sy, ex, ey;

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    while(~scanf("%lld%lld%d", &n, &m, &q)){
        ll g = gcd(n, m);
        while(q --){
            scanf("%lld%lld%lld%lld", &sx, &sy, &ex, &ey);
            ll sn = (ll)ceil(1.0 * g * sy / n);
            ll sm = (ll)ceil(1.0 * g * sy / m);
            ll en = (ll)ceil(1.0 * g * ey / n);
            ll em = (ll)ceil(1.0 * g * ey / m);
            // printf("%lld %lld %lld %lld\n", sn, sm, en, em);
            ll x1, x2;
            if(sx == 1) {
                x1 = sn;
            }
            else {
                x1 = sm;
            }
            if(ex == 1) {
                x2 = en;
            }
            else {
                x2 = em;
            }
            // printf("%lld %lld\n", x1, x2);
            if(x1 == x2){
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }
        }
    }
    return 0;
}
