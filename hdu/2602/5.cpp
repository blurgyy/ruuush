#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1010;
typedef long long ll;

int T, n, v;
ll value[maxn], volume[maxn];
ll dp[maxn];

int main(){
    scanf("%d", &T);
    while(T--){
        memset(dp, 0, sizeof(dp));
        scanf("%d%d", &n, &v);
        for(int i = 1; i <= n; ++ i)
            scanf("%lld", value + i);
        for(int i = 1; i <= n; ++ i)
            scanf("%lld", volume + i);
        for(int j = 1; j <= n; ++ j){               //遍历所有种类的物品
            for(int i = v; i >= volume[j]; -- i){   //从v到0遍历背包容量，对于每一个容量i，判断拿当前种类的物品是否会使总价值更大，若是，则取当前物品，更新dp[i]的值。
                                                    //若从0到v遍历，则当背包容量较大时，会造成一个物品取了多次的情况。于是造成最终结果变很大。
                                                    //从0到v遍历是完全背包问题的解法
                dp[i] = max(dp[i], dp[i-volume[j]] + value[j]);
            }
        }
        printf("%lld\n", dp[v]);
    }
    return 0;
}

/**

1
5 10
1 2 3 4 5
5 4 3 2 1

*/