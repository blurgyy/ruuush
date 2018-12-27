#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int len;
char s[maxn];
int pref[maxn];

bool check(int x){
    int lastpos = 0;
    int curpos;
    for(curpos = 1; curpos <= len; ++ curpos){
        if(pref[curpos] - pref[lastpos] == x){
            lastpos = curpos;
        }
        else if(pref[curpos] - pref[lastpos] > x){
            return false;
        }
    }
    return lastpos == len || pref[len] - pref[lastpos] == 0;
}

int main(){
    while(~scanf("%d%s", &len, s + 1)){
        bool ans = false;
        for(int i = 1; i <= len; ++ i){
            pref[i] = pref[i-1] + s[i] - '0';
        }
        for(int i = 1; i < pref[len]; ++ i){
            if(pref[len] % i)continue;
            if(check(i)){
                ans = true;
                break;
            }
        }
        if(ans || pref[len] == 0){
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}