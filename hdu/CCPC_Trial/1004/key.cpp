#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int M = 1e6+10;
const int MOD = 1e9+7;
char str1[M];
char str2[M];
int len1,len2 ;
void get_next(int * next){
    int k = -1;
    int j =  0;
        next[0] = -1;
    while(j < len2){
        if( k == -1 || str2[j] == str2[k]){
            next[++ j] = ++ k;
        }
        else{
            k = next[k];
        }
    }
}
int main(){
    int t;
    scanf("%d",&t);
    int next[M];
    int dp[M];
    while(t --){
        memset(str1,0,sizeof(str1));
        memset(str2,0,sizeof(str2));
        scanf("%s%s",str1,str2);
        len1 = strlen(str1);
        len2 = strlen(str2);
        for(int i = 0 ; i < len1 / 2  ; i ++ ){
            char c = str1[i];
            str1[i] = str1[len1-1-i];
            str1[len1-1-i] = c;
        }
        for(int i = 0 ; i < len2/2 ; i ++ ){
            char c = str2[i];
            str2[i] = str2[len2-1-i];
            str2[len2-1-i] = c;
        }
        get_next(next);
        memset(dp,0,sizeof(dp));
        for(int i = 1 ; i <= len2 ; i ++ ){
            if(next[i] == 0){
                dp[i] = i;
                continue;
            }
            dp[i] = dp[next[i]] + i ;
            dp[i] %= MOD;
        }
        /*for(int i = 1 ; i <= len2 ; i ++ ){
            dp[i] += 1;
        }*/
        for(int i = 1 ; i <= len2 ; i ++ ){
            dp[i] += dp[i-1];
            dp[i] %= MOD;
            //cout << dp[i] << " ";
        }
       //b cout << endl;
        int i = 0 ;
        int j = 0;
        long long num = 0;
        int flag = 0;
        while(i < len1){
            if(str1[i] == str2[j]){
                ++ i ;
                ++ j ;
            }
            else{
                num += dp[ j ] - dp[flag - i + j ];
                flag = i;
                j = next[j];
                if(j == -1 ){
                    ++ i;
                    j = 0 ;

                }
            }
            if(j == len2){
                num += dp[ j ] - dp[flag - i + j ];
                num %= MOD;
                flag = i;
                j = next[j];
                if(j == -1){
                    j = 0;
                }
            }
            //cout << i << endl;
        }
        if(j != 0){
            num += dp[ j ] - dp[flag - i + j ];
            num %= MOD;
        }
        cout << num << endl;
    }


    return 0;
}
