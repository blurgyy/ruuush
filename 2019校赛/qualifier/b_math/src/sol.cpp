#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;

ll dp[maxn][maxn][2];

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        dp[0][0][0] = dp[0][0][1] = 0;
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= n; ++ j){
                dp[i][j][1] = dp[i-1][j][1] + dp[i-1][j-1][1] + 2 * dp[i-1][j-1][0];
                dp[i][j][0] = dp[i-1][j+1][1] + dp[i-1][j+1][0] + dp[]
            }
        }
    }
    return 0;
}
