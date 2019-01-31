#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 100010;

int n, m;
int a[maxn], c[maxn];
pii chn[maxn];

int main(){
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1; i <= n; ++ i) scanf("%d", a + i);
        for(int i = 1; i <= n; ++ i) scanf("%d", c + i);
        for(int i = 1; i <= n; ++ i) chn[i] = make_pair(c[i], i);
        sort(chn+1, chn+1 + n);
        int cur = 1;
        int t, d;
        for(int i = 1; i <= m; ++ i){
            ll cost = 0;
            scanf("%d%d", &t, &d);
            if(a[t] >= d){
                a[t] -= d;
                cost += 1ll * d * c[t];
                d = 0;
            }
            else {
                // printf("(else)");
                cost += 1ll * a[t] * c[t];
                // printf("(%d, %d)\n", a[t], c[t]);
                d -= a[t];
                a[t] = 0;
                for(; cur <= n; ++ cur){
                    int id = chn[cur].second;
                    if(a[id] <= 0){
                        continue;
                    }
                    if(a[id] >= d){
                        a[id] -= d;
                        cost += 1ll * d * c[id];
                        d = 0;
                        break;
                    }
                    else {
                        // printf("((else)) %lld\n", cost);
                        cost += 1ll * a[id] * c[id];
                        d -= a[id];
                        a[id] = 0;
                    }
                }
            }
            if(d > 0) cost = 0;
            printf("%lld\n", cost);
        }
    }
    return 0;
}