#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n;
ll s;
ll v[maxn];

int main(){
	v[0] = 0;
	while(~scanf("%d%lld", &n, &s)){
		ll overall_sum = 0;
		for(int i = 1; i <= n; ++ i){
			scanf("%lld", v + i);
			overall_sum += v[i];
		}
		sort(v+1, v+1 + n);
		ll sum = 0;
		int pos = -1;
		for(int i = n-1; i >= 0; -- i){
			sum += 1ll * (n-i) * (v[i+1] - v[i]);
			if(sum >= s){
				pos = i;
				break;
			}
		}
		if(sum < s){
			printf("-1\n");
			continue;
		}
		else if(sum == s){
			printf("%lld\n", v[min(1, pos)]);
			continue;
		}
		else {
			printf("%lld\n", (1ll * n * v[pos+1] - (s - (overall_sum - (1ll * n * v[pos+1])))) / n);
		}
	}
	return 0;
}