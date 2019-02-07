#include <bits/stdc++.h>
using namespace std;

int x;

int main(){
	int cnt = 0;
	while(~scanf("%d", &x)){
	// for(int x = 3; x < 2147483647; x = x * 2 + 1){
		int ans = -1;
		for(int i = 1; i < x; ++ i){
			int x1 = x^i;
			int x2 = x&i;
			ans = max(ans, __gcd(x1, x2));
		}
		printf("%d: %d\n", ++ cnt, ans);
	}
	return 0;
}