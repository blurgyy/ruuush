#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;
const int mod = 1e9 + 7;

int T, n;
int lst[maxn];
ll w[maxn];

int main(){
    // while(~scanf("%d", &n)){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        for(int i = 0; i < n; ++ i){
            scanf("%lld", w + i);
            lst[i] = i;
        }
        random_shuffle(lst, lst + n);
        ll v = 1;
        ll ans = 0;
        for(int i = 0; i < n; ++ i){
            // ans += v * w[lst[i]];
            // v += v * w[lst[i]];
            ans = (ans + v * w[lst[i]] % mod) % mod;
            v = (v + v * w[lst[i]] % mod) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
