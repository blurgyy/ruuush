#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, a[maxn], ans, current;

int main(){
	while(~scanf("%d", &n) && n){
		ans = 0, current = 0;
		for(int i = 0; i < n; ++ i){
			scanf("%d", a + i);
			if(a[i] > current)
				ans += 6 * (a[i] - current);
			else ans += 4 * (current - a[i]);
			current = a[i];
			ans += 5;
		}
		printf("%d\n", ans);
	}
	return 0;
}