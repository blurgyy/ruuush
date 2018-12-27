#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
typedef long long ll;

int n, a[maxn], p;
ll rec[maxn];
bool vis[maxn];

ll sq(ll a){
    return a * a;
}

int main(){
    while(~scanf("%d", &n)){
        memset(vis, false, sizeof(vis));
        p = 0;
        for(int i = 1; i <= n; ++ i)
            scanf("%d", a + i);
        for(int i = 1; i <= n; ++ i){
            if(vis[i])continue;
            int nxt = a[i], cnt = 1;
            vis[nxt] = true;
            while(nxt != i){
                nxt = a[nxt];
                vis[nxt] = true;
                ++ cnt;
            }
            rec[p++] = cnt;
        }
        if(p == 1){
            printf("%I64d\n", sq(rec[0]));
            continue;
        }
        sort(rec, rec + p);
        rec[p-2] += rec[p-1];
        -- p;
        ll ans = 0;
        for(int i = 0; i < p; ++ i)
            ans += sq(rec[i]);
        printf("%I64d\n", ans);
    }
    return 0;
}