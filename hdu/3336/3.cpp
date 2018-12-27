#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;
const int mod = 10007;

int T, n;
int nxt[maxn];
char s[maxn];

void getnxt(char *s){
    //memset(nxt, 0, sizeof(nxt));
    nxt[0] = -1;
    int i = 0, j = -1;
    while(i <= n){
        if(j == -1 || s[i] == s[j])
            nxt[++i] = ++ j;
        else j = nxt[j];
    }
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%s", &n, s);
        getnxt(s);
        for(int i = 0; i <= n; ++ i){
            printf("%d%c", nxt[i], " \n"[i == n]);
        }
    }
    return 0;
}