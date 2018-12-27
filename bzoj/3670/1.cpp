#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int mod = 1e9 + 7;

int n, nxt[maxn], len, num[maxn];
char s[maxn];

void getnxt(){
    int i = 0, j = -1;
    memset(nxt, 0, sizeof(nxt));
    nxt[0] = -1;
    while(i <= len){
        if(j == -1 || s[i] == s[j])
            nxt[++i] = ++ j;
        else j = nxt[j];
    }
}

int main(){
    scanf("%d", &n);
    while(n--){
        scanf("%s", s);
        len = strlen(s);
        getnxt();
        memset(num, 0, sizeof(num));
        for(int i = 1; i < len; ++ i){
            int prv = nxt[i];
            while(prv >= (i+1)/2)
                prv = nxt[prv];
            if(prv < 0)prv = 0;
            //num[i] = (s[prv] == s[i]) * (num[prv] + (s[i] == s[0] ? 0 : 1)) + (s[i] == s[0]);
            //num[i] = (s[prv] == s[i]) * (num[prv] + (s[i] == s[prv])) + (prv != 0 && s[prv] != s[0]) * (s[i] == s[0]);
            //printf("prv[%c] = %d\n", s[i], prv);
            num[i] = (prv ? num[prv-1] : 0) + nxt[i+1] 
        }
        for(int i = 0; i < len; ++ i)
            printf("%d%c", num[i], " \n"[i == len-1]);
        ll ans = 1;
        for(int i = 0; i < len; ++ i)
            ans = (ans * ((ll)num[i] + 1LL)) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}