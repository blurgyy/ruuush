#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull inf = 0xffffffffffffffff;
const ull half = 0x8000000000000000;

int T;
ull a, b;

int main(){
	scanf("%d", &T);
	while(T --){
		scanf("%llu%llu", &a, &b);
		if(a == half && b == half){
			printf("18446744073709551616\n");
			continue;
		}
		printf("%llu\n", a + b);
	}
	return 0;
}
