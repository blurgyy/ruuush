#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1010;

int n, m;
int dp[maxn], price[maxn];

int main(){
    while(~scanf("%d", &n) && n){
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; ++ i)
            scanf("%d", price + i);
        scanf("%d", &m);
        if(m < 5){
            printf("%d\n", m);
            continue;
        }
        sort(price + 1, price + 1 + n);
        int maxv = m - 5;
        for(int i = 1; i < n; ++ i)//贪心：dp过程中不选最贵的菜
            for(int j = maxv; j >= price[i]; -- j)
                dp[j] = max(dp[j], dp[j-price[i]] + price[i]);
        printf("%d\n", m - dp[maxv] - price[n]);
    }
    return 0;
}