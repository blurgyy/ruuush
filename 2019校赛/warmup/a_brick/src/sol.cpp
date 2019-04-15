#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 100010;
const int mod = 1e9 + 7;

int T, n;
ll w;

ull k1, k2;
ull xorShift128Plus(unsigned int MAXW = 2147483647){ // maxwi <= MAX_INT
	ull k3 = k1, k4 = k2;
	k1 = k4;
	k3 ^= k3 << 23;
	k2 = k3 * k4 ^ (k3 >> 17) ^ (k4 >> 26);
	return (k2 + k4) % MAXW;
}

int main(){
    scanf("%d", &T);
    while(T --){
    	scanf("%d%llu%llu", &n, &k1, &k2);
    	ll ans = 1;
    	for(int i = 0; i < n; ++ i){
    		ull x = xorShift128Plus() + 1;
    		ans = (ans * x) % mod;
    	}
    	printf("%lld\n", (ans - 1 + mod) % mod);
    }
    return 0;
}
