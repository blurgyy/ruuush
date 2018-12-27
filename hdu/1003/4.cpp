///CRAP...

//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100010;
const int INF = -1000000000;

int T, Case = 0;
int n, a[maxn], dp[maxn], len[maxn];

int main(){
    //freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T--){
        memset(a, 0, sizeof(a));
        for(int i = 0; i < maxn; ++ i)
            dp[i] = INF;
        memset(len, 0, sizeof(len));
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i)
            scanf("%d", a + i);
        for(int i = 1; i <= n; ++ i){
            if(a[i] > dp[i-1] + a[i]){
                dp[i] = a[i];
                len[i] = 0;
            }
            else{
                dp[i] = dp[i-1] + a[i];
                len[i] = len[i-1] + 1;
            }
        }
        int ans = INF, pos = -1;
        for(int i = 1; i <= n; ++ i){
            if(ans < dp[i]){
                ans = dp[i];
                pos = i;
            }
        }
        if(Case)printf("\n");
        printf("Case %d:\n%d %d %d\n", ++ Case, ans, pos - len[pos], pos);
    }
    return 0;
}