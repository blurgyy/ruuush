#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1510;
const int inf = 0x3f3f3f3f;

int T, n;
int a[maxn];
int pref[maxn], suf[maxn];
int dp[maxn];   //dp[i] = dp[j] + sum(k: j to i-1)[(i-k) * a[k]] + sum(k: i+1 to n)a[k]
                //in which, dp[j] = min(dp[1 to i-1])

int presum(int pos, int now){
    int ret = 0;
    for(int i = pos; i < now; ++ i){
        ret += (now - i) * a[i];
    }
    return ret;
}

void init(){
    memset(a, 0, sizeof(a));
    memset(dp, 0x3f, sizeof(dp));
    memset(pref, 0, sizeof(pref));
}

int main(){
    //freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            pref[i] = pref[i-1] + a[i];
        }
        printf("pref[%d] = %d\n", n, pref[n]);
        dp[1] = pref[n] - pref[1];
        int pos = 1, minx = pref[n];
        for(int i = 2; i <= n; ++ i){
            dp[i] = dp[pos] + presum(pos, i) + pref[n] - pref[i];
            if(dp[i] < minx){
                pos = i;
                minx = dp[i];
            }
        }
        for(int i = 1; i <= n; ++ i){
            printf("dp[%d] = %d\n", i, dp[i]);
        }
        printf("\n");
    }
    return 0;
}