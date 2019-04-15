#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef unsigned int uint;
const int mod = 1e9+7;
const ull inf = 0x3f3f3f3f3f3f3f3f;

ull k1, k2;
ull xorShift128Plus(unsigned int maxwi = 2147483647){ // maxwi <= MAX_INT
	ull k3 = k1, k4 = k2;
	k1 = k4;
	k3 ^= k3 << 23;
	k2 = k3 * k4 ^ (k3 >> 17) ^ (k4 >> 26);
	return (k2 + k4) % maxwi;
}

int main(){
	// k1 = 498;
	// k2 = 25229;
	// ull n1 = xorShift128Plus() + 1;
	// ull n2 = xorShift128Plus() + 1;
	// printf("%llu, %llu, prod = %llu\n", n1, n2, n1 * n2);
	// return 0;
	for(ull i = 100000; i; -- i){
		for(ull j = 100000; j; -- j){
			k1 = i;
			k2 = j;
			ull n1 = xorShift128Plus() + 1;
			// ull n2 = xorShift128Plus() + 1;
			// ull ans = n1 * n2 % (mod+1);
			ull ans = n1 % mod;
			if(ans == 0 && n1 != 0){
				printf("when k1 = %llu and k2 = %llu, ", i, j);
				printf("%llu %% %llu = 0\n", n1, ans);
			}
		}
	}
	return 0;
}


