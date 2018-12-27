//wrong move...

#include<bits/stdc++.h>
using namespace std;
const int maxn = 60;

int N, R, F[maxn], S[maxn];
double ans, prob[maxn];

int inline Sum(int *a, int pos, bool reverse = false){
	int sum = 0;
	if(reverse){
		for(int i = N-1; i > pos; -- i)
			sum += a[i];
		return sum;
	}
	for(int i = 0; i < pos-1; ++ i)
		sum += a[i];
	return sum;
}

int inline check(){
	if(Sum(S, 0, true) +S[0] <= R)return 0;
	for(int i = 0; i < N; ++ i){
		if(Sum(S, i, true) + Sum(F, i) + F[i] <= R)return i+1;
	}
}

int main(){
	while(~scanf("%d%d", &N, &R)){
		ans = 0;
		for(int i = 0; i < N; ++ i){
			scanf("%d%d%lf", F + i, S + i, prob + i);
		}
		int must_fast = check();
		printf("%d\n", must_fast);
		double P = 1.0;
		for(int i = 0; i < must_fast; ++ i){
			//ans += F[i] + ((100 - prob[i])/prob[i]) * S[i];
			P *= prob[i]/100;
		}
		printf("P = %f\n", P);
		if(must_fast)
			ans += Sum(F, must_fast) + (Sum(S, must_fast, true) + S[must_fast]) * ((1-P)/P);
		printf("ans = %f\n", ans);
		for(int i = must_fast; i < N; ++ i){
			ans += (F[i] * prob[i] + S[i] * (100 - prob[i])) / 100;
		}
		printf("final ans = %f\n\n", ans);
	}
	return 0;
}

/**

160.169365358
64.97752808988764

*/