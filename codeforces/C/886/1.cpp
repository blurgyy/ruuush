#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n, t[maxn], ans;
bool vis[maxn];

int main(){
    while(~scanf("%d", &n)){
        ans = 0;
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= n; ++ i)
            scanf("%d", t + i);
        for(int i = n; i > 0; -- i){
            if(vis[i])continue;
            ++ ans;
            int nxt = t[i];
            while(/*t[nxt] >= 0*/nxt){
                vis[nxt] = true;
                nxt = t[nxt];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}