#include<bits/stdc++.h>
using namespace std;
const int maxn = 30;

int n, a[maxn];
int pref[maxn];

int main(){
    while(~scanf("%d", &n)){
        scanf("%d", a);
        pref[0] = a[0];
        for(int i = 1; i < n; ++ i){
            scanf("%d", a + i);
            pref[i] = pref[i-1] + a[i];
        }
        int ans[maxn] = {0}, p = 0, sum = 0;
        bool vis[maxn] = {false};
        for(int i = 0; i < n-1; ++ i){
            int val = -1;
            for(int j = 0; j < n; ++ j){
                if(vis[j])continue;
                if(a[j] != a[i] && a[j] + sum != pref[i]){
                    vis[j] = true;
                    val = a[j];
                    break;
                }
            }
            if(-1 < val){
                ans[p++] = val;
                sum += val;
            }
        }
        if(p == n-1){
            for(int i = 0; i < n; ++ i)
                if(!vis[i]){
                    ans[p++] = a[i];
                    break;
                }
            for(int i = 0; i < p; ++ i)
                printf("%d%c", ans[i], " \n"[i == p-1]);
        }
        else printf("-1\n");
    }
    return 0;
}