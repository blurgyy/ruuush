#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 510;

int n;
struct ASDDF{
	int deg, id;
	bool operator< (const ASDDF &rhs){
		return deg < rhs.deg;
	}
}a[maxn];
int checker;
pii ans[maxn<<3];
int p = 0;

int main(){
	while(~scanf("%d", &n)){
		p = 0;
		checker = 0;
		for(int i = 1; i <= n; ++ i){
			a[i].id = i;
			scanf("%d", &a[i].deg);
			if(i == 1)checker = a[i].deg;
			else checker += a[i].deg - 2;
		}
		if(checker < 0) printf("NO\n");
		else {
			sort(a+1, a+1 + n);
			// for(int i = 1; i <= n; ++ i){
			// 	printf("a[%d] = (%d, %d)\n", i, a[i].id, a[i].deg);
			// }
			printf("YES ");
			int pos = 0;
			for(int i = n-1; i; -- i){
				ans[p++] = make_pair(a[i].id, a[i+1].id);
				a[i].deg --;
				a[i+1].deg --;
				if(a[i].deg == 0){
					pos = i;
					break;
				}
			}
			// printf("p = %d\n", p);
			if(pos <= 1){
				// printf("(pos = %d) <= 1!!!\n", pos);
				printf("%d\n", n-1);
				printf("%d\n", p);
				for(int i = 0; i < p; ++ i){
					printf("%d %d\n", ans[i].first, ans[i].second);
				}
			}
			else {
				// printf("(pos = %d) > 1!!!\n", pos);
				int rear = n;
				int diam = n - pos + 1;
				for(int i = 1; i < pos && a[i].deg > 0; ++ i){
					while(a[rear].deg <= 0) rear --;
					ans[p++] = make_pair(a[i].id, a[rear].id);
					a[i].deg --;
					a[rear].deg --;
				}
				printf("%d\n", diam);
				printf("%d\n", p);
				for(int i = 0; i < p; ++ i){
					printf("%d %d\n", ans[i].first, ans[i].second);
				}
			}
		}
	}
	return 0;
}