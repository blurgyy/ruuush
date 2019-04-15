#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;
const int mod = 1e9 + 7;

int T, n;
ll w;

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        ll ans = 1;
        while(n --){
            scanf("%lld", &w);
            ans = ans * (w + 1) % mod;
        }
        printf("%lld\n", (ans-1 + mod) % mod);
    }
    return 0;
}
