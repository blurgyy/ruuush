#include <bits/stdc++.h>
using namespace std;
const int maxn = 210;
const int maxd = 10010;

int n;
int d[maxn];
int cnt[maxd];

int main(){
    while(~scanf("%d", &n)){
        memset(cnt, 0, sizeof(cnt));
        int maxx = -1;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", d + i);
            cnt[d[i]] ++;
            maxx = max(maxx, d[i]);
        }
        int ans1 = maxx, ans2 = -1;
        for(int i = maxx; i; -- i){
            if(cnt[i] > 0 && maxx % i == 0){
                cnt[i] --;
            }
        }
        for(int i = ans1; i; -- i){
            if(cnt[i]){
                ans2 = i;
                break;
            }
        }
        while(ans1 < 0 || ans2 < 0);
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}