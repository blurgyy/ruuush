#include <bits/stdc++.h>
using namespace std;

int main(){
	srand(time(NULL));
	printf("%lld %lld\n", 1ll * rand() * rand() % (long long)1000000000000000000 + 7, 1ll * rand() * rand() % (long long)1000000000000 + 7);	
	return 0;
}