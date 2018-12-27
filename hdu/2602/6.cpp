#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;
typedef long long ll;

int T;
int N, V;
ll v[maxn], w[maxn], dp[maxn];

int main(){
    scanf("%d", &T);
    while(T--){
        memset(dp, 0, sizeof(dp));
        scanf("%d%d", &N, &V);
        for(int i = 0; i < N; ++ i)
            scanf("%lld", v + i);
        for(int i = 0; i < N; ++ i)
            scanf("%lld", w + i);
        for(int i = 0; i < N; ++ i){
            for(int j = V; j >= w[i]; -- j){
                if(dp[j] < dp[j-w[i]] + v[i])
                    dp[j] = dp[j-w[i]] + v[i];
            }
        }
        printf("%lld\n", dp[V]);
    }
    return 0;
}