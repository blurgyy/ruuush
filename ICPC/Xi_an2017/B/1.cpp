#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MOD = 1000000007;

int T;
ll p, q, k;
ll x, y;

ll fp(ll a, ll b)
{
    ll ans = 1;
    while(b)
    {
        if(b&1)ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

int get_inv(ll n){
	if(n == 1)return 1;
	return (MOD - MOD/n)*get_inv(MOD % n) % MOD;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%lld%lld%lld", &p, &q, &k);
		y = fp(p, k);
		x = ((y + fp(p-2*q, k))) % MOD * 500000004 % MOD;
		y = get_inv(y);
		//printf("x = %lld, y = %lld\n", x, y);
		printf("%lld\n", (x * y) % MOD);
	}
	return 0;
}