#include <cstdio>
typedef long long ll;
const int maxn = 1000010;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;

int T, n;
ll a[maxn];
ll ans;

ll inv(ll x){
	return x == 1 ? 1 : (mod - mod % x) * inv(mod % x) % mod;
}

int main(){
	scanf("%d")
	/////WRONG ATTEMPT
}