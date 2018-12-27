#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const ll mod = 1e9 + 7;

int n, nxt[maxn], len, num[maxn], rec[maxn];
char s[maxn];

void getnxt(){
    int i = 0, j = -1;
    for(int i = 1; i <= len; ++ i)
        nxt[i] = 0;
    while(i <= len){
        if(j == -1 || s[i] == s[j])
            nxt[++i] = ++ j;
        else j = nxt[j];
    }
}

int calc(int pos){
    if(pos < 1)return 0;
    if(rec[pos] == -1){
        rec[pos] = (s[pos] == s[nxt[pos]]) * calc(nxt[pos]) + (nxt[pos+1] != 0);
    }
    return rec[pos];
}

int main(){
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    nxt[0] = -1;
    memset(rec, -1, sizeof(rec));
    scanf("%d", &n);
    while(n--){
        scanf("%s", s);
        len = strlen(s);
        getnxt();
        //for(int i = 0; i < len; ++ i)
            //nxt[i] = nxt[i+1];
        memset(num, 0, sizeof(num));
        /*printf("nxt:\t");
        for(int i = 0; i < len; ++ i)
            printf("%d%c", nxt[i], " \n"[i == len-1]);*/
        for(int i = 1; i < len; ++ i){
            int prv = nxt[i];
            while(prv >= ((i + 1) >> 1))
                prv = nxt[prv];
            //printf("prv = %d, ", prv);
            //num[i] = (s[i] == s[prv]) * num[prv] + (nxt[i+1] != 0);
            num[i] = (s[i] == s[prv]) * calc(prv) + (nxt[i+1] != 0);
            //printf("num[%d] = %d\n", i, num[i]);
        }
        /*printf("num:\t");
        for(int i = 0; i < len; ++ i)
            printf("%d%c", num[i], " \n"[i == len-1]);*/
        ll ans = 1;
        for(int i = 0; i < len; ++ i)
            ans = (ans * ((ll)num[i] + 1LL)) % mod;
        printf("%lld\n", ans);
        for(int i = 0; i < len; ++ i)
            rec[i] = -1;
    }
    return 0;
}

/**

aaaaa
0 1 1 2 2

*/