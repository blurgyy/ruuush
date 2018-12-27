#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;
const int mod = 10007;

int T, n, nxt[maxn], jmp[maxn];
char s[maxn];

void getnxt(){
    nxt[0] = -1;
    memset(jmp, 0, sizeof(jmp));
    int i = 0, j = -1;
    while(i <= n){
        if(j == -1 || s[i] == s[j]){
            nxt[++i] = ++ j;
            if(nxt[i] <= 0)continue;
            jmp[i] = jmp[nxt[i]] + 1;
        }
        else j = nxt[j];
    }
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%s", &n, s);
        getnxt();
        int dp[maxn] = {0};
        for(int i = 1; i <= n; ++ i){
            dp[i] = (dp[i-1] + jmp[i] + 1) % mod;
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}