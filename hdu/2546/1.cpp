#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, m;
int price[maxn];
int dp[maxn][maxn];

int main(){
    while(~scanf("%d", &n) && n){
        for(int i = 0; i < n; ++ i)
            scanf("%d", price + i);
        scanf("%d", &m);
        sort(price, price + n);
        if(m - 5 - price[0] >= 0){
            for(int i = 1; i < n; ++ i){
                for(int j = n; j > 1; -- j){
                    dp[i][j] = max(dp[i][j], dp[i-1][j] - price[j]);
                }
            }
        }
        printf("%d\n", m - price[n-1]);
    }
    return 0;
}