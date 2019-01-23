#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int len;
char s[maxn];
char ret[maxn];
int lk[3][maxn];
int dp[3][maxn];    /// R for 0, G for 1, B for 2

int minid(int pos){
    if(dp[0][pos] <= dp[1][pos] && dp[0][pos] <= dp[2][pos]) return 0;
    if(dp[1][pos] <= dp[0][pos] && dp[1][pos] <= dp[2][pos]) return 1;
    return 2;
}

char chch(int x){
    if(x == 0)return 'R';
    if(x == 1)return 'G';
    return 'B';
}

char *seq(int clr, int pos){
    ret[pos+1] = 0;
    for(int i = pos; i >= 0; -- i){
        ret[i] = chch(clr);
        clr = lk[clr][i];
    }
    return ret;
}

int main(){
    while(~scanf("%d%s", &len, s)){
        memset(dp, 0 ,sizeof(dp));
        memset(lk, 0, sizeof(lk));
        dp[0][0] = s[0] != 'R';
        dp[1][0] = s[0] != 'G';
        dp[2][0] = s[0] != 'B';
        for(int i = 1; i < len; ++ i){
            if(s[i] == 'R'){
                dp[0][i] = min(dp[1][i-1], dp[2][i-1]); // R
                if(dp[1][i-1] <= dp[2][i-1]){
                    lk[0][i] = 1;
                }
                else {
                    lk[0][i] = 2;
                }
                dp[1][i] = dp[2][i] = dp[0][i-1] + 1; // G, B
                lk[1][i] = lk[2][i] = 0;
            }
            else if(s[i] == 'G'){
                dp[1][i] = min(dp[0][i-1], dp[2][i-1]); // G
                if(dp[0][i-1] <= dp[2][i-1]){
                    lk[1][i] = 0;
                }
                else {
                    lk[1][i] = 2;
                }
                dp[0][i] = dp[2][i] = dp[1][i-1] + 1; // R, B
                lk[0][i] = lk[2][i] = 1;
            }
            else if(s[i] == 'B'){
                dp[2][i] = min(dp[0][i-1], dp[1][i-1]); // B
                if(dp[0][i-1] <= dp[1][i-1]){
                    lk[2][i] = 0;
                }
                else {
                    lk[2][i] = 1;
                }
                dp[0][i] = dp[1][i] = dp[2][i-1] + 1; // R, G
                lk[0][i] = lk[1][i] = 2;
            }
            else {
                while(true);
            }
        }
        // for(int i = 0; i < 3; ++ i){
        //     for(int j = 0; j < len; ++ j){
        //         printf("%d", lk[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("dp:\n");
        // for(int i = 0; i < 3; ++ i){
        //     for(int j = 0; j < len; ++ j){
        //         printf("%d", dp[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("%d\n", min(dp[0][len-1], min(dp[1][len-1], dp[2][len-1])));
        int id = minid(len-1);
        printf("%d\n%s\n", dp[id][len-1], seq(id, len-1));
    }
    return 0;
}