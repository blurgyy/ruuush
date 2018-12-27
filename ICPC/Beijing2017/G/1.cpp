#include<bits/stdc++.h>
using namespace std;

int n, m, ans;
int len;
int minus;

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a%b);
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		if(n > m)swap(n, m);
		if((m-n)%(n-1) == 0){
			printf("%d\n", m);
			continue;
		}
		len = n + (n-1) * m / gcd(n-1, m);

	}
	return 0;
}