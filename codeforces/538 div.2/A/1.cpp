#include <bits/stdc++.h>
using namespace std;

int A, D, M;
int a, b, c;

int main(){
	while(~scanf("%d%d%d%d%d%d", &A, &D, &M, &a, &b, &c)){
		a -= A;
		if(a < 0){
			printf("NO\n");
			continue;
		}
		if(a + b < D){
			printf("NO\n");
			continue;
		}
		int sum = a + b + c - D - M;
		if(sum < 0){
			printf("NO\n");
			continue;
		}
		printf("YES\n");
	}
	return 0;
}
