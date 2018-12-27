#include<bits/stdc++.h>
using namespace std;
const int maxn = 30;

int n, m;
int a[maxn], b[maxn];

int main(){
	while(~scanf("%d%d", &n, &m)){
		for(int i = 0; i < n; ++ i)
			scanf("%d", a + i);
		for(int i = 0; i < m; ++ i)
			scanf("%d", b + i);
		sort(a, a + n);
		sort(b, b + m);
		int mn = 1000;
		for(int i = 0; i < n; ++ i)
			for(int j = 0; j < m; ++ j)
				if(a[i] == b[j])mn = min(mn, a[i]);
		if(mn != 1000){
			printf("%d\n", mn);
			continue;
		}
		printf("%d%d\n", min(a[0], b[0]), max(a[0], b[0]));
	}
	return 0;
}