#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int T, n, ans, here, there;
int a[maxn], dp[maxn];
int start[maxn];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		memset(dp, 0, sizeof(dp));
		memset(start, 0, sizeof(start));
		ans = here = there = 0;
		for(int i = 1; i <= n; ++ i){
			scanf("%d", a + i);
			if(dp[i-1] + a[i] <= a[i]){
				dp[i] = a[i];
				start[i] = i;
			}
			else dp[i] = dp[i-1] + a[i];
		}
		for(int i = 1; i <= n; ++ i)
			if(ans < dp[i]){
				ans = dp[i];
				for(int j = i; j > 0; -- j)
					if(start[j]){
						here = j;
						break;
					}
				there = i;
				break;
			}
		printf("%d %d %d\n", ans, here, there);
	}
	return 0;
}

/**

2
5 6 -1 5 4 -7
7 0 6 -1 1 -6 7 -5

*/