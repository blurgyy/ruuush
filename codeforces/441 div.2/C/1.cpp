#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n;
int ans[maxn], p;

bool check(int x){
	int sum = x;
	//printf("x = %d\n", x);
	while(x){
		//printf("x%10 = %d\n", x%10);
		sum += x%10;
		x /= 10;
	}
	//if(sum == n)return true;
	//return false;
	return sum == n;
}

int main(){
	while(~scanf("%d", &n)){
		memset(ans, 0, sizeof(ans));
		p = 0;
		for(int i = 1; i < maxn && i <= n; ++ i){
			if(check(n-i))
				ans[p++] = n-i;
		}
		printf("%d\n", p);
		sort(ans, ans + p);
		for(int i = 0; i < p; ++ i)
			printf("%d\n", ans[i]);
	}
	return 0;
}