#include <bits/stdc++.h>
using namespace std;
const int maxn = 150010;
const char nons = '=';

int rad[maxn<<1];
char s[maxn];

int manacher(char *x){
    int ret = -1;
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
        ret = max(ret, rad[i] - 1);
    }
    return ret;
}

int main(){
    while(~scanf("%s", s + 1)){
        printf("%d\n", manacher(s));
    }
    return 0;
}