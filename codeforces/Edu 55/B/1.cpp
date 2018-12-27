#pragma optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n, p, posp;
char s[maxn];
int l[maxn], r[maxn];
int ans[maxn];

int main(){
    while(~scanf("%d%s", &n, s + 1)){
        p = 0;
        for(int i = 1; i <= n; ++ i){
            if(s[i] == 'G' && s[i-1] != 'G') l[p] = i;
            if(s[i] == 'G' && s[i+1] != 'G') r[p++] = i;
        }
        // for(int i = 0; i < p; ++ i){
        //     printf("(%d to %d)\n", l[i], r[i]);
        // }
        if(p == 0){
            printf("0\n");
            continue;
        }
        else if(p == 1){
            printf("%d\n", r[0] - l[0] + 1);
            continue;
        }
        else {
            int ans = 0;
            for(int i = 0; i < p; ++ i){
                int curlen = r[i] - l[i] + 1;
                ans = max(ans, curlen);
            }
            // printf("ans = %d\n", ans);
            if(p == 2){
                if(l[1] == r[0] + 2){
                    ans = r[1] - l[0];
                }
            }
            else {
                for(int i = 1; i < p; ++ i){
                    if(l[i] == r[i-1] + 2){
                        ans = max(ans, r[i] - l[i-1] + 1);
                    }
                }
            }

            printf("%d\n", ans);
        }
    }
    return 0;
}