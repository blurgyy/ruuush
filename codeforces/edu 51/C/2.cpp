#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
const char *out = "AB";

int n;
int s[maxn];
int side, cnt1;
bool vis[maxn];
int cnt[maxn];

int main(){
    while(~scanf("%d", &n)){
        side = 0;
        cnt1 = 0;
        memset(cnt, 0, sizeof(cnt));
        memset(vis, false, sizeof(vis));
        for(int i = 0; i < n; ++ i){
            scanf("%d", s + i);
            cnt[s[i]] ++;
        }
        for(int i = 0; i < n; ++ i){
            if(cnt[s[i]] == 1){
                cnt1 ++;
            }
        }
        if(cnt1 & 1){
            printf("NO");
        }
        else {
            printf("YES\n");
            for(int i = 0; i < n; ++ i){
                if(cnt[s[i]] == 1){
                    printf("%c", out[side]);
                    side = 1 - side;
                    vis[s[i]] = true;
                }
            }
            for(int i = 0; i < n; ++ i){
                if(cnt[s[i]] & 1){
                    if(!vis[s[i]]){
                        printf("%c", out[side]);
                        side = 1 - side;
                        vis[s[i]] = true;
                    }
                    else {
                        printf("%c", out[side]);
                    }
                }
                else {
                    printf("A");
                }
            }
        }
        printf("\n");
    }
    return 0;
}