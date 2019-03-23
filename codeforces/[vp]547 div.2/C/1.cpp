#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;
const int inf = 0x3f3f3f3f;

int n;
int dif[maxn];
ll perm[maxn];
bool vis[maxn];

bool inrange(ll x){return x >= 0 && x < maxn;}

int main(){
    while(~scanf("%d", &n)){
        ll ini = 0;
        ll minx = 0;
        n --;
        for(int i = 0; i < n; ++ i){
            scanf("%d", dif + i);
            ini += dif[i];
            minx = min(minx, ini);
        }
        bool ans = true;
        memset(vis, false, sizeof(vis));
        perm[1] = -minx + 1;
        if(!inrange(perm[1])){
            printf("-1\n");
            continue;
        }
        vis[perm[1]] = true;
        for(int i = 0; i < n; ++ i){
            perm[i+2] = perm[i+1] + dif[i];
            if(!inrange(perm[i+2])){
                ans = false;
                break;
            }
            vis[perm[i+2]] = true;
        }
        if(!ans){
            printf("-1\n");
            continue;
        }
        n ++;
        for(int i = 1; i <= n; ++ i){
            if(vis[i] == false){
                ans = false;
                break;
            }
        }
        if(ans){
            for(int i = 1; i <= n; ++ i){
                printf("%lld%c", perm[i], " \n"[i==n]);
            }
        }
        else {
            printf("-1\n");
        }
    }
    return 0;
}
