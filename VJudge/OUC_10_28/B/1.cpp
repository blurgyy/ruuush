#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;
const int rdcst = 1510;

ll n, k;
int power[maxn];
bool vis[maxn];
ll cnt[510];

int main(){
    while(~scanf("%I64d%I64d", &n, &k)){
        for(int i = 0; i < maxn; ++ i)
        vis[i] = true;
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= n; ++ i)
            scanf("%d", power + i);
        int p = n + 1;
        int top = 1, sec = 2;
        int ans = 0;
        for(int i = 2; ; ++ i){
            if(power[top] > power[i]){
                power[p++] = power[i];
            }
            else {
                top = i;
            }
            ++ cnt[power[top]];
            if(cnt[power[top]] >= k || cnt[power[top]] >= rdcst){
                ans = power[top];
                break;
            }
        }
        /*
        while(true){
            if(power[top] > power[sec]){
                cnt[top] ++;
                power[p++] = power[sec];
                vis[sec] = false;
                if(cnt[top] >= k || cnt[top] >= rdcst){
                    ans = top;
                    break;
                }
            }
            else{
                power[p++] = power[top];
                //while(!vis[++top]);
                cnt[sec] ++;
                if(cnt[sec] >= k || cnt[sec] >= rdcst){
                    ans = sec;
                    break;
                }
                top = sec;
                sec ++;
            }
        }*/
        printf("%d\n", ans);
    }
    return 0;
}
