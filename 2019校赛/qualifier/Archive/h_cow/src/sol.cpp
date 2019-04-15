#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int T, n;
struct A{
	int p, v;
	bool operator< (A &rhs){
		// return v == rhs.v ? p < rhs.p : v < rhs.v;
		return p == rhs.p ? v < rhs.v : p < rhs.p;
	}
}a[maxn];

int main(){
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++ i){
			scanf("%d%d", &a[i].p, &a[i].v);
		}
		sort(a+1, a+1 + n);
		int maxx = -1;
		int ans = 0;
		for(int i = 1; i <= n; ++ i){
			maxx = max(maxx, a[i].v);
			if(maxx == a[i].v) {
				ans ++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
