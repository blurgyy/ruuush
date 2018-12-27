#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n;
int a[maxn];

int main(){
	while(~scanf("%d", &n)){
		int ans = 0;
		for(int i = 0; i < n; ++ i){
			scanf("%d", a + i);
			ans += 4 * i * a[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}