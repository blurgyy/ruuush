#include"bits/stdc++.h"
using namespace std;
typedef long long LL;
const int MX = 1e6+7;
const int INF = 0x3f3f3f3f;
int n;
char s[MX];
bool ch[256];
int x,y;
int dp[MX][2];
void init()
{
    ch['a'] = ch['e'] = ch['i'] = ch['o'] = ch['u'] = 1;
}
inline void upd0(int i)
{
    dp[i][0] = dp[i-1][0] + 1;
    dp[i][1] = 0;
}
inline void upd1(int i)
{
    dp[i][1] = dp[i-1][1] + 1;
    dp[i][0] = 0;
}
bool get_mav()
{
    dp[0][0] = dp[0][1] = 0;
    for(int i = 1; i <= n; i++){
        if(s[i] == '?'){
            upd0(i);
        }
        else if(ch[s[i]]){
            upd0(i);
        }
        else{
            upd1(i);
        }
        if(dp[i][0] >= x || dp[i][1] >= y) return 1;
    }
    return 0;
}
 
bool get_mac()
{
    dp[0][0] = dp[0][1] = 0;
    for(int i = 1; i <= n; i++){
        if(s[i] == '?'){
            upd1(i);
        }
        else if(ch[s[i]]){
            upd0(i);
        }
        else{
            upd1(i);
        }
        if(dp[i][0] >= x || dp[i][1] >= y) return 1;
    }
    return 0;
}
 
bool get_min()
{
    for(int i = 0; i <= n; i++)
        dp[i][0] = dp[i][1] = INF;
    dp[0][0] = dp[0][1] = 0;
    for(int i = 1; i <= n; i++){
        if(s[i] == '?'){
            if(dp[i-1][0] < x){
                dp[i][0] = min(dp[i][0], dp[i-1][0]+1);
                dp[i][1] = min(dp[i][1], 1);
            }
            if(dp[i-1][1] < y){
                dp[i][0] = min(dp[i][0], 1);
                dp[i][1] = min(dp[i][1], dp[i-1][1]+1);
            }
        }
        else if(ch[s[i]]){
            if(dp[i-1][0] < x){
                 dp[i][0] = min(dp[i][0],dp[i-1][0]+1);
            }
            if(dp[i-1][1] < y){
                dp[i][0] = min(dp[i][0],1);
            }
        }
        else{
            if(dp[i-1][1] < y){
                dp[i][1] = min(dp[i][1],dp[i-1][1] + 1);
            }
            if(dp[i-1][0] < x){
                dp[i][1] = min(dp[i][1],1);
            }
        }
        if(dp[i][0] >= x && dp[i][1] >= y) return 0;
    }
    return 1;
}
 
int main()
{
#ifdef LOCAL
    freopen("input.txt","r",stdin);
#endif // LOCAL
    int T,cas = 0;
    init();
    scanf("%d",&T);
    while(T--) {
        scanf("%s %d %d",s+1,&x,&y);
        printf("Case #%d: ",++cas);
        n = strlen(s+1);
        bool maxx = 0, minx = 0;
        maxx |= get_mav();
        maxx |= get_mac();
        minx |= get_min();
 
        if(!maxx) printf("LIKE\n");
        else if(!minx) printf("DISLIKE\n");
        else printf("SURPRISE\n");
    }
    return 0;
}
