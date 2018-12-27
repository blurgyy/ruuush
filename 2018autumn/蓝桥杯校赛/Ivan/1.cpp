#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100;
const int maxp = 10000010;
const int mod = 998244353;

int T, n, l, r;
int a[maxn];
ll x[maxp];
ll pref[maxp];

int main(){
    // freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        scanf("%d%d%d", &n, &l, &r);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        sort(a+1, a+1+n);
        x[0] = pref[0] = 1;
        for(int i = 1; i <= a[1]; ++ i){
            x[i] = 1;
            pref[i] = pref[i-1] + 1;
            if(pref[i] >= mod) pref[i] -= mod;
            // printf("pref[%d] = %lld\n", i, pref[i]);
        }
        int maxpow = a[1];
        int top = a[1];
        for(int i = 2; i <= n; ++ i){
            // if(a[i] == 0)break;
            top = maxpow + a[i];
            for(int j = 1; j <= top; ++ j){
                if(j - a[i] - 1 < 0) x[j] = pref[min(j,maxpow)];
                else {
                    if(j > maxpow) x[j] = pref[maxpow] - pref[j-a[i]-1];
                    else x[j] = pref[j] - pref[j-a[i]-1];
                    if(x[j] < 0) x[j] += mod;
                }
                //else x[j] = (pref[min(j,maxpow)] - pref[j-a[i]-1] + mod) % mod;
            }
            for(int j = 1; j <= top; ++ j){
                // pref[j] = (pref[j-1] + x[j]) % mod;
                pref[j] = pref[j-1] + x[j];
                if(pref[j] >= mod) pref[j] -= mod;
                // if(j == r){
                    // printf("pref[%d] = %lld\n", j, pref[j]);
                // }
            }
            maxpow = top;

            for(int j = 0; j <= top; ++ j){
                printf("%lld%c", x[j], " \n"[j==top]);
            }
            // for(int j = 0; j <= top; ++ j){
            //     printf("%lld%c", pref[j], " \n"[j==top]);
            // }
        }
        // printf("top = %d\n", top);
        ll ans = -1;
        if(l == 0){
            // printf("r = %d\n", r);
            ans = pref[min(top,r)];// % mod;
        }
        else {
            // printf("r = %d\n", r);
            ans = (pref[min(top,r)] - pref[min(top,l-1)] + mod) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}