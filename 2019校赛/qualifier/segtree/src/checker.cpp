#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int T;
int n, m;
int a[maxn];

int calc(){
	int maxx = -1;
	int ret = 0;
	for(int i = 1; i <= n; ++ i){
		if(maxx < a[i]){
			maxx = a[i];
			ret ++;
		}
	}
	return ret;
}

int main(){
	scanf("%d", &T);
	while(T --){
		scanf("%d%d", &n, &m);
		int pos, x;
		while(m --){
			scanf("%d%d", &pos, &x);
			a[pos] = x;
			printf("%d\n", calc());
		}
	}
	return 0;
}
