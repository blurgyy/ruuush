#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 30010;

int n, mod;
int fib[maxn];
ll a[maxn];
ll tmp[maxn];

int main(){
    fib[0] = fib[1] = 1;
    while(~scanf("%d%d", &n, &mod)){
        for(int i = 2; i < maxn; ++ i)
            fib[i] = (fib[i-1] + fib[i-2]) % mod;
        for(int i = 1; i <= n; ++ i)
            scanf("%d", a + i);
        int q, l, r, p;
        scanf("%d", &q);
        while(q--){
            p = 0;
            scanf("%d%d", &l, &r);
            ll ans = 0;
            for(int i = l; i <= r; ++ i)
                tmp[p++] = a[i];
            sort(tmp, tmp + p);
            p = unique(tmp, tmp + p) - tmp;
            for(int i = 0; i < p; ++ i){
                //printf("i = %d\n", i);
                ans = (ans + tmp[i] * fib[i]) % mod;
            }
            printf("%I64d\n", ans);
        }
    }
    return 0;
}