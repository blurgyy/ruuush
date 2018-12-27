#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;
const char nons = '_';

int rad[maxn<<1];
int nxt[maxn];
int mlen[maxn];
int n;
char s[maxn], t[maxn];

void getnext(char *T){
    int j, k;
    j = 0; k = -1; nxt[0] = -1;
    int tlen = strlen(T);
    while(j < tlen){
        if(k == -1 || T[j] == T[k])
            nxt[++j] = ++k;
        else
            k = nxt[k];
    }
    for(int i = tlen; i > 0; -- i){
        nxt[i] = nxt[i-1];
    }
}

int manacher(char *x){
    int len = strlen(x + 1) * 2 + 1;
    char s[maxn<<1] = {0};
    for(int i = 1; i <= len; ++ i){
        if(i & 1){
            s[i] = nons;
        }
        else {
            s[i] = x[i/2];
        }
    }
    int pos = 0, maxr = 0;
    for(int i = 1; i <= len; ++ i){
        if(i < maxr){
            rad[i] = min(rad[pos-i+pos], maxr - i);
        }
        else {
            rad[i] = 1;
        }
        while(i - rad[i] > 0 && i + rad[i] <= len && s[i-rad[i]] == s[i+rad[i]]){
            rad[i] ++;
        }
        if(i + rad[i] - 1 > maxr){
            maxr = i + rad[i] - 1;
            pos = i;
        }
    }
}

void init(){
    for(int i = 1; i <= n; ++ i){
        s[i] = t[n-i+1];
    }
    getnext(t + 1);
    
}

int main(){
    while(~scanf("%d%s", &n, t + 1)){
        init();
    }
    return 0;
}