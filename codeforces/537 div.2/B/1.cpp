#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const size_t maxn = 100010;

int n, k, m;
ll a[maxn];
ll pref[maxn];

int main(){
    pref[0] = 0;
    while(~scanf("%d%d%d", &n, &k, &m)){
        for(int i = 1; i <= n; ++ i){
            scanf("%lld", a + i);
        }
        sort(a+1, a+1 + n);
        for(int i = 1; i <= n; ++ i){
            pref[i] = pref[i-1] + a[i];
        }
        double ans = 0;
        for(int b = 0; b <= m; ++ b){
            ll X = pref[n] - pref[b];
            ll Y = n - b;
            if(Y <= 0) break;
            ans = max(ans, (double(X) + min(Y*k, 1ll*m-b)) / double(Y));
            // printf("ans = %f\n", ans);
        }
        printf("%.10f\n", ans);
    }
    return 0;
}