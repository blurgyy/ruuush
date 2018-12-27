#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 20010;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int T, Case = 0;
ll n, s, m, k;
ll a[maxn];
ll pref[maxn];
ll ans;
bool vis[maxn];

void init(){
    memset(pref, 0, sizeof(pref));
    memset(vis, false, sizeof(vis));
    ans = inf;
}

int main(){
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%lld%lld%lld%lld", &n, &s, &m, &k);
        for(int i = 0; i < n; ++ i){
            scanf("%lld", a + i);
        }
        for(int i = 0; i < n; ++ i){
            if(vis[i] == false){
                vis[i] = true;
                int p = 1;
                pref[p++] = a[i];
                int now = i, nxt = (now + k) % n;
                while(vis[nxt] == false){
                    vis[nxt] = true;
                    pref[p++] = a[nxt];
                    now = nxt;
                    nxt = (now + k) % n;
                }
                int len = m % (p - 1), t = m / p;
                /*
                printf("p = %d\n", p);
                for(int i = 1; i <= p; ++ i){
                    printf("%lld%c", pref[i], " \n"[i == p-1]);
                }
                */
                for(int i = 1; i <= p; ++ i){
                    pref[p+i] = pref[i];
                }
                p *= 2;
                for(int i = 1; i <= p; ++ i){
                    pref[i] = pref[i-1] + pref[i];
                }
                int r = len;
                ll maxx = pref[len];
                while(r <= p){
                    maxx = max(maxx, pref[r] - pref[r-len]);
                    r ++;
                }
                //printf("maxx = %lld\n", maxx);
                maxx += t * pref[p] / 2;
                ll cur = s - maxx;
                ans = min(ans, cur);
                //printf("ans = %lld\n", ans);
                if(ans <= 0)break;
            }
        }
        ans = max(0LL, ans);
        printf("Case #%d: %lld\n", ++ Case, ans);
    }
    return 0;
}

/**

2
3 10 5 2
3 2 1
5 20 6 3
2 3 2 1 5

*/