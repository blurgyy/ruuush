#include <bits/stdc++.h>
typedef long long ll;

int main(){
	srand(time(NULL));
	ll T = rand();
	printf("%lld\n", T);
	while(T --){
		printf("%lld\n", ((ll)rand() * (ll)rand()) % (ll)1004535809 + (ll)rand());
	}
	return 0;
}