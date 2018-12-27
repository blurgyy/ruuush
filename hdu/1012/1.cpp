#include<bits/stdc++.h>
using namespace std;

double e = 0;

double mm(int a){
	if(!a)return (double)1;
	int ans = 1;
	for(int i = 1; i <= a; ++ i)
		ans *= i;
	return (double)ans;
}

int main(){
	printf("n e\n");
	printf("- -----------\n");
	printf("0 1\n1 2\n2 2.5\n3 2.666666667\n4 2.708333333\n");
	for(int i = 0; i < 10; ++ i){
		e += (1/mm(i));
		if(i > 4)printf("%d %.9f\n", i, e);
	}
	return 0;
}