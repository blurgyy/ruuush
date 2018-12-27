#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100;
const int maxp = 10000010;
const int mod = 998244353;

int T, n, l, r;
int a[maxn];
ll x[maxp];
ll roll[maxp];

int main(){
    freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        scanf("%d%d%d", &n, &l, &r);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        sort(a+1, a+1+n);
        for(int i = 0; i <= a[1]; ++ i){
            x[i] = roll[i] = 1;
        }
        int maxpow = a[1];
        int top = a[1];
        for(int i = 2; i <= n; ++ i){
            // if(a[i] == 0)break;
            top = maxpow + a[i];
            ll acc = 1;
            for(int j = 1; j <= top; ++ j){
                if(j <= maxpow)acc += x[j];
                if(acc >= mod) acc -= mod;
                // printf("out: acc = %lld\n", acc);
                if(j - a[i] - 1 < 0){
                    x[j] = acc;
                }
                else {
                    acc -= roll[j-a[i]-1];
                    roll[j-a[i]-1] = x[j-a[i]-1];
                    if(acc < 0) acc += mod;
                    // printf("(%d, %d) - acc = %lld\n", j-a[i]-1, j, acc);
                    x[j] = acc;
                }
            }
            maxpow = top;
            for(int j = top-a[i]-1; j <= top; ++ j){
                roll[j] = x[j];
            }

            // for(int j = 0; j <= top; ++ j){
            //     printf("%lld%c", x[j], " \n"[j==top]);
            // }
        }
        // printf("top = %d\n", top);
        ll ans = 0;
        for(int i = l; i <= r; ++ i){
            ans = ans + x[i];
            if(ans >= mod) ans -= mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}