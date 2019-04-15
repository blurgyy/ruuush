#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 110;

int T;
int n, m;
ll fac[maxn];

ll A(int m, int n){
	if(m < n) return 0;
	ll ret = fac[m] / fac[n] / fac[m-n];
	return ret * fac[n];
}

int main(){
	fac[0] = 1;
	for(int i = 1; i < maxn; ++ i){
		fac[i] = fac[i-1] * i;
	}
	scanf("%d", &T);
	while(T --){
		scanf("%d%d", &n, &m);
		printf("%lld\n", A(m, n));
	}
	return 0;
}
