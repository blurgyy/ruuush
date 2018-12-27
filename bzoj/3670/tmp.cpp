#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int mod = 1e9 + 7;

int n, len;
int assis[maxn], nxt[maxn], router[maxn], num[maxn];
char s[maxn];

void getnxt(){
    int i = 0, j = -1;
    memset(nxt, 0, sizeof(nxt));
    nxt[0] = -1;
    while(i <= len){
        if(j == -1 || s[i] == s[j])
            nxt[++ i] = ++ j;
        else j = nxt[j];
    }
}

void adjust(){
    int i = 0, j = -1;
    memset(assis, 0, sizeof(assis));
    assis[0] = -1;
    while(i <= len){
        if(j == -1 || j < ((i)>>1) && s[i] == s[j])
            assis[++i] = ++ j;
        else j = nxt[j];
    }
}

void init(){
    len = strlen(s);
    memset(router, 0, sizeof(router));
    memset(num, 0, sizeof(num));
}

int main(){
    scanf("%d", &n);
    while(n--){
        scanf("%s", s);
        init();
        getnxt();
        adjust();
        for(int i = 1; i <= len; ++ i)
            printf("%d%c", assis[i], " \n"[i == len]);
        for(int i = 1; i < len; ++ i)
            router[i] = (s[i] == s[nxt[i]]) * router[nxt[i]] + (nxt[i+1] != 0);

        ll ans = 1;
        printf("0 ");
        for(int i = 1; i < len; ++ i){
            num[i] = (s[i] == s[assis[i]]) * num[assis[i]] + (assis[i+1] != 0);
            printf("%d%c", num[i], " \n"[i == len-1]);
            ans = (ans * (num[i] + 1)) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}