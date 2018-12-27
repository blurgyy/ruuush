#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int T, x, y, len;
char s[maxn];
int dp[2][maxn];

bool vowel(char ch){
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

void init(){
    len = strlen(s + 1);
    for(int i = 1; i <= len; ++ i){
        if(vowel(s[i])){
            s[i] = 'a';
        }
        else if(s[i] == '?');
        else {
            s[i] = 'b';
        }
    }
    memset(dp, 0x3f, sizeof(dp));
}

bool check(){
    dp[0][0] = dp[1][0] = 0;
    for(int i = 1; i <= len; ++ i){
        if(s[i] == '?'){
            if(dp[0][i-1] < x){
                dp[0][i] = dp[0][i-1] + 1;
                dp[1][i] = 1;
            }
            if(dp[1][i-1] < y){
                dp[0][i] = min(dp[0][i], 1);
                dp[1][i] = min(dp[1][i], dp[1][i-1] + 1);
            }
        }
        else if(s[i] == 'a'){
            if(dp[0][i-1] < x){
                dp[0][i] = dp[0][i-1] + 1;
            }
            if(dp[1][i-1] < y){
                dp[0][i] = min(dp[0][i], 1);
            }
        }
        else {
            if(dp[1][i-1] < y){
                dp[1][i] = dp[1][i-1] + 1;
            }
            if(dp[0][i-1] < x){
                dp[1][i] = min(dp[1][i], 1);
            }
        }
        //printf("%d\t%d\n", dp[0][i], dp[1][i]);
        if(dp[0][i] >= x && dp[1][i] >= y){
            return false;
        }
    }
    return true;
}

int main(){
    scanf("%d", &T);
    int Case = 0;
    while(T --){
        scanf("%s%d%d", s+1, &x, &y);
        printf("Case #%d: ", ++ Case);
        init();
        //printf("%s\n", s + 1);
        if(!check()){
            printf("DISLIKE\n");
            continue;
        }

        bool surprise = false;
        dp[0][0] = dp[1][0] = 0;
        for(int i = 1; i <= len; ++ i){
            if(s[i] == 'a' || s[i] == '?'){
                dp[0][i] = dp[0][i-1] + 1;
                dp[1][i] = 0;
            }
            else {
                dp[0][i] = 0;
                dp[1][i] = dp[1][i-1] + 1;
            }
            if(dp[0][i] >= x || dp[1][i] >= y){
                surprise = true;
                break;
            }
        }
        dp[0][0] = dp[1][0] = 0;
        for(int i = 1; i <= len; ++ i){
            if(s[i] == 'b' || s[i] == '?'){
                dp[1][i] = dp[1][i-1] + 1;
                dp[0][i] = 0;
            }
            else {
                dp[1][i] = 0;
                dp[0][i] = dp[0][i-1] + 1;
            }
            if(dp[0][i] >= x || dp[1][i] >= y){
                surprise = true;
                break;
            }
        }
        if(surprise){
            printf("SURPRISE\n");
        }
        else {
            printf("LIKE\n");
        }

    }
    return 0;
}