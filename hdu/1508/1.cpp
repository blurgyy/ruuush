///把maxn从1010改成100010就A了
//wtf

//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 10010;
typedef long long ll;

char seq[maxn];
ll dp[maxn];

bool check(int pos){
    return (seq[pos-1] - '0') * 10 + (seq[pos] - '0') <= 26;
}

int main(){
    while(~scanf("%s", seq+1) && strcmp(seq+1, "0")){
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        int len = strlen(seq+1);
        for(int i = 1; i <= len; ++ i){
            if(seq[i] == '0')dp[i] = dp[i-2];
            else if(seq[i] >= '1' && seq[i] <= '6'){
                if(seq[i-1] == '1' || seq[i-1] == '2')
                    dp[i] = dp[i-1] + dp[i-2];
                else dp[i] = dp[i-1];
            }
            else if(seq[i-1] == '1'){
                dp[i] = dp[i-1] + dp[i-2];
            }
            else dp[i] = dp[i-1];
            //printf("dp[%d] = %d\n", i, dp[i]);
        }
        printf("%lld\n", dp[len]);
    }
    return 0;
}