#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;

ll n;
ll x[maxn], y[maxn], a[maxn], b[maxn];

int main(){
    while(~scanf("%I64d", &n)){
        ll xsum = 0, ysum = 0;
        ll asum = 0, bsum = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%I64d%I64d", x + i, y + i);
            xsum += x[i];
            ysum += y[i];
        }
        for(int i = 1; i <= n; ++ i){
            scanf("%I64d%I64d", a + i, b + i);
            asum += a[i];
            bsum += b[i];
        }
        printf("%I64d %I64d\n", (xsum + asum) / n, (ysum + bsum) / n);
    }
    return 0;
}