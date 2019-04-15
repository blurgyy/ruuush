#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int T, n;
int nxt[maxn];
bool vis[maxn];

ll lcm(ll a, ll b){return a * b / __gcd(a, b);}

ll calc(int x){
    ll ret = 1;
    vis[x] = true;
    x = nxt[x];
    while(vis[x] == false){
        vis[x] = true;
        ret ++;
        x = nxt[x];
    }
    return ret;
}

void transform(int len = n){
    int mid = len / 2 + 1;
    nxt[mid] = 1;
    for(int i = 2, shift = -1; i <= len; ++ i){
        nxt[mid + shift] = i;
        if(shift < 0) shift = -shift;
        else shift = -shift - 1;
    }
    // for(int i = 1; i <= len; ++ i){
    //     printf("%d%c", nxt[i], " \n"[i==len]);
    // }
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        memset(vis, false, sizeof(vis));
        transform(n);
        ll ans = 1;
        for(int i = 1; i <= n; ++ i){
            if(vis[i] == true) continue;
            ll now = calc(i);
            if(now) ans = lcm(ans, now);
        }
        printf("%lld\n", ans - 1);
    }
    return 0;
}
