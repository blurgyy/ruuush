#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1010;
typedef long long ll;

int T, n, v;
ll value[maxn], volume[maxn];
ll dp[maxn];//dp[i]表示 恰装满容量为i的背包时，最大能获得的价值

int main(){
	scanf("%d", &T);
	while(T--){
		memset(dp, 0, sizeof(dp));//MUST...
		scanf("%d%d", &n, &v);
		for(int i = 1; i <= n; ++ i)
			scanf("%lld", value + i);
		for(int i = 1; i <= n; ++ i)
			scanf("%lld", volume + i);
		for(int i = 1; i <= n; ++ i){
			for(int vol = v; vol >= volume[i]; -- vol)
				dp[vol] = max(dp[vol], dp[vol-volume[i]] + value[i]);
		}
		printf("%lld\n", dp[v]);
	}
	return 0;
}