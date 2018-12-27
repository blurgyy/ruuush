#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, p;
double cst;

double proba(int x){
	double ans = x;
	for(int j = 2; j <= x; ++ j){
		ans *= (double)(n-p+j)/(double)(n+j);
	}
	//printf("ans = %.12f\n", ans*cst);
	return ans*cst;
}

int main(){
	while(~scanf("%lld%lld", &n, &p)){
		cst = (double)p / (double)(n+1);
		printf("%.8f\n", proba(n/(p-1)));
	}
	return 0;
}