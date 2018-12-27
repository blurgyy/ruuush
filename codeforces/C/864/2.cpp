#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;
typedef long long ll;

ll a, b, f, k;

int main(){
	while(~scanf("%I64d%I64d%I64d%I64d", &a, &b, &f, &k)){
		if(b == f && 2*b == a && k == 1){
			printf("1\n");
			continue;
		}
		if(k == 1 && a == b){
			printf("0\n");
			continue;
		}
		if(k > 2 && (b < f || b < 2*(a-f) || b < 2*f)){
			printf("-1\n");
			continue;
		}
		if(k == 2 && (b < 2*a - f)){
			printf("-1\n");
			continue;
		}
		if(k == 1 && b < f || b < a-f){
			printf("-1");
			continue;
		}
		int ans = 0, now = b - f;
		ll total_length = k*a, cnt = f;
		int even_or_odd = 1;
		while(cnt < total_length){
			if(even_or_odd&1){//if odd
				if(cnt + 2*(a-f) >= total_length){
					now -= total_length - cnt;
					if(now < 0)
						++ ans;
					break;
				}
				now -= 2*(a-f);
				cnt += 2*(a-f);
				if(now < 0){
					++ ans;
					now = b - 2*(a-f);
					if(now < 0){
						ans = 0;
						break;
					}
				}
			}
			else{
				if(cnt + 2*a >= total_length){
					now -= total_length - cnt;
					if(now < 0)
						++ ans;
					break;
				}
				now -= 2*f;
				cnt += 2*f;
				if(now < 0){
					++ ans;
					now = b - 2*f;
					if(now < 0){
						ans = 0;
						continue;
					}
				}
			}
			++ even_or_odd;
		}
		printf("%d\n", ans);
	}
	return 0;
}