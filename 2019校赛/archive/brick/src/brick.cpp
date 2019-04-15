#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;

int T, n;
bool vis[maxn];
ll w[maxn];
ll sum;

ll calc(int pos){
	return (1 + sum - w[pos]) * w[pos];
}

int main(){
	// scanf("%d", &T);
	T = -1;
	while(T --){
		sum = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++ i){
			scanf("%lld", w + i);
			sum += w[i];
		}

		ll maxx = -1;
		ll ans = 0;
		int pos = -1;
		memset(vis, false, sizeof(vis));
		for(int t = 0; t < n; ++ t, maxx = -1, pos = -1){
			for(int i = 1; i <= n; ++ i){
				if(vis[i]) continue;
				ll val = calc(i);
				// printf("val = %lld\n", val);
				if(maxx < val){
					maxx = val;
					pos = i;
				}
			}
			ans += maxx;
			printf("ans += %lld\n", maxx);
			vis[pos] = true;
			sum -= w[pos];
		}
		// printf("max last = w[%d] = %lld\n", pos, w[pos]);
		printf("%lld\n", ans);
	}
	return 0;
}
