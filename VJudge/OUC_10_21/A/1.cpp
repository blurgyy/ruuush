#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n, a[maxn], pos[maxn], p;
char s[maxn];

int main(){
	while(~scanf("%d%s", &n, s)){
		for(int i = 0; i < n; ++ i)
			scanf("%d", a + i);
		for(int i = 1; i < n; ++ i)
			if(s[i-1] == 'R' && s[i] == 'L')
				pos[p++] = i;
		if(p == 0){
			printf("-1\n");
			continue;
		}
		int ans = 0x3f3f3f3f;
		for(int i = 0; i < p; ++ i)
			ans = min(ans, (a[pos[i]] - a[pos[i]-1])/2);
		printf("%d\n", ans);
	}
	return 0;
}