#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;

int T, k;
char s[maxn];

int main(){
    freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T--){
        scanf("%s%d", s, &k);
        int f = 0, r = 1;
        ll ans = 0, cnt = 1;
        int len = strlen(s);
        int vis[300] = {0};
        vis[s[0]] ++;
        while(r <= len){
            if(cnt >= k){
                ans += len - r + 1;
                f ++;
                if(vis[s[f-1]] == 1){
                    cnt --;
                }
                vis[s[f-1]] --;
            }
            else {
                r ++;
                if(vis[s[r-1]] == 0){
                    cnt ++;
                }
                vis[s[r-1]] ++;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}