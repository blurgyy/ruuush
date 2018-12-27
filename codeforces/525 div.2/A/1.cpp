#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int x;
int ansa, ansb;

bool check(int &a, int &b){
	return a % b == 0 && a * b > x && 1.0*a / b < 1.0*x;
}

int main(int argc, char const *argv[]){
	while(~scanf("%d", &x)){
		if(x == 1) printf("-1\n");
		else printf("%d %d\n", x, x);
		// ansa = ansb = 0;
		// for(int a = 1; a <= x; ++ a){
		// 	for(int b = 1; b <= x; ++ b){
		// 		if(check(a, b)){
		// 			ansa = a;
		// 			ansb = b;
		// 			break;
		// 		}
		// 		if(ansa || ansb)break;
		// 	}
		// }
		// if(ansa == 0 && ansb == 0) printf("-1\n");
		// else printf("%d %d\n", ansa, ansb);
	}	
	return 0;
}