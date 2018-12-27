#include<bits/stdc++.h>
using namespace std;

int n, a, b, c;

int main(){
	while(~scanf("%d%d%d%d", &n, &a, &b, &c)){
		n -= 1;
		if(!n){
			printf("0\n");
			continue;
		}
		if(n == 1){
			printf("%d\n", min(a, b));
			continue;
		}
		int mn = min(a, min(b, c));
		if(a == mn || b == mn){
			printf("%d\n", n * mn);
			continue;
		}
		printf("%d\n", (n - 1) * mn + min(a, b));
	}
	return 0;
}