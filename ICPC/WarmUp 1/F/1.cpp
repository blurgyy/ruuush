#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mt(ll n){
	ll ret = 1;
	for(ll i = 2; i <= n; ++ i)
		ret *= i;
	return ret;
}

ll C(ll a, ll b){
	ll ans = 1;
	ans = (mt(a) / mt(a-b)) / mt(b);
	//printf("ans = %lld\n", ans);
	return ans;
}

ll n, p;

int main(){
	double ans = 1;
	while(~scanf("%d%d", &n, &p)){
		//printf("%d\n", mt(23));
		ll time = 0;
		double prev = 0, now = 1;
		for(ll ans = 1; time < 20; ++ ans, ++ time){
			now = ((double)C(n, p-1) * 1.0 * ans/ (double)C(n+ans, p));
			printf("%f\n", now);
			prev = now;
		}
	}
	return 0;
}