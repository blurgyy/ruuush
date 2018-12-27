#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn = 1010;
typedef long long ll;

int T, N, V;
ll volume[maxn], value[maxn];
ll dp[maxn][maxn];          //dp[i][j] = max(dp[i-1][j], dp[i-1][j-volume[i]] + value[i]);

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &N, &V);
        for(int i = 1; i <= N; ++ i)
            scanf("%lld", value + i);
        for(int i = 1; i <= N; ++ i)
            scanf("%lld", volume + i);
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= N; ++ i){
            for(int j = volume[i]; j <= V; ++ j)
                dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-volume[i]] + value[i]);
        }
        printf("%d\n", dp[N][V]);
    }
    return 0;
}