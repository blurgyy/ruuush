///last one was a fake solution
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;

int T, x, y;
char s[maxn];
int len;
int dp[2][maxn];
int rec[maxn], tot;

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
}

bool check(){
    dp[0][0] = dp[1][0] = 0;
    for(int i = 1; i <= len; ++ i){
        if(s[i] == '?'){
            if(s[i-1] == 'a'){
                dp[0][i] = dp[0][i-1] + 1;
                dp[1][i] = 1;
            }
            else if(s[i-1] == 'b'){
                dp[1][i] = dp[1][i-1] + 1;
                dp[0][i] = 1;
            }
            else {
                dp[0][i] = dp[1][i] = 1;
            }
            if(dp[0][i-1] == x - 1 && s[i-1] == 'a' || dp[1][i-1] == y - 1 && s[i-1] == 'b'){
                return false;
            }
            if(dp[0][i-1] == x - 1){
                dp[0][i] = x;
                dp[1][i] = dp[1][i-1] + 1;
                s[i] = 'b';
            }
            else if(dp[1][i-1] == y - 1){
                dp[1][i] = y;
                dp[0][i] = dp[0][i-1] + 1;
                s[i] = 'a';
            }
            else {
                dp[0][i] = dp[1][i] = 1;
            }
        }
        else if(s[i] == 'a'){
            if(s[i-1] == 'a'){
                dp[0][i] = dp[0][i-1] + 1;
            }
            else {
                dp[0][i] = 1;
            }
            dp[1][i] = 0;
        }
        else {
            if(s[i-1] == 'b'){
                dp[1][i] = dp[1][i-1] + 1;
            }
            else {
                dp[1][i] = 1;
            }
            dp[0][i] = 0;
        }
        if(s[i] == 'a' && dp[0][i] >= x || s[i] == 'b' && dp[1][i] >= y){
            return false;
        }
    }
    return true;
}

int main(){
    scanf("%d", &T);
    int Case = 0;
    while(T --){
        scanf("%s%d%d", s + 1, &x, &y);
        printf("Case #%d: ", ++ Case);
        init();
        if(!check()){
            printf("DISLIKE\n");
            continue;
        }
        bool surprise = false;
        dp[0][0] = dp[1][0] = 0;
        for(int i = 1; i <= len; ++ i){
            if(s[i] == 'a' || s[i] == '?'){
                dp[0][i] = dp[0][i-1] + 1;
            }
            if(s[i] == 'b' || s[i] == '?'){
                dp[1][i] = dp[1][i-1] + 1;
            }
            if(dp[0][i] >= x || dp[1][i] >= y){
                surprise = true;
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