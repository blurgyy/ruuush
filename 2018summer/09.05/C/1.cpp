#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int d, r, t;
int cnt[maxn];

int main(){
    cnt[0] = 0;
    for(int i = 1; i < maxn; ++ i)
        cnt[i] = cnt[i-1] + i;
    while(~scanf("%d%d%d", &d, &r, &t)){
        int ans = -1;
        for(int i = 4; i < maxn; ++ i){
            int rage = cnt[i] - cnt[3];
            int tage = cnt[i-d] - cnt[2];
            //printf("%d %d\n", r - rage, tage - t);
            if(r - rage == tage - t){
                ans = r - rage;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}