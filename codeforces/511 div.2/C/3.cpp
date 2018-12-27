#include <bits/stdc++.h>
using namespace std;
const int maxn = 300010;
const int maxpri = 15000010;

int n;
int a[maxn];
int cnt[maxn];
bool vis[maxpri];

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    while(~scanf("%d", &n)){
        memset(cnt, 0, sizeof(cnt));
        memset(vis, false, sizeof(vis));
        int g = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            g = gcd(g, a[i]);
        }
        int maxx = -1;
        for(int i = 0; i < n; ++ i){
            a[i] /= g;
            cnt[a[i]] ++;
            maxx = max(maxx, a[i]);
        }
        int ans = 1e9;
        for(int pri = 2; pri <= maxx; ++ pri){
            if(!vis[pri]){
                int x = pri;
                int reserved = 0;
                while(x <= maxx){
                    vis[x] = true;
                    reserved += cnt[x];
                    x += pri;
                }
                ans = min(ans, n - reserved);
            }
        }
        if(ans == 1e9){
            printf("-1\n");
        }
        else {
            printf("%d\n", ans);
        }
    }
    return 0;
}