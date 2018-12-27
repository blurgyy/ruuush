#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

int ans[10] = {0,1,3,7,13,22,31,43,60,83};

int main(){
	for(int t = 0; t < 10; ++ t){
		for(int i = 0; i < 9-t; ++ i){
			ans[i] = ans[i+1] - ans[i];
		}
		for(int i = 0; i < 9-t; ++ i){
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	return 0;
}