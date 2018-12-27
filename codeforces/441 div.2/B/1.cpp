#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, k, m, pos;
int a[maxn], mod[maxn], cnt[maxn];

void init(){
	memset(cnt, 0, sizeof(cnt));
	pos = INF;
}

int main(){
	//freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
	while(~scanf("%d%d%d", &n, &k, &m)){
		init();
		for(int i = 0; i < n; ++ i){
			scanf("%d", a + i);
			mod[i] = a[i] % m;
			++ cnt[mod[i]];
		}
		/*for(int i = 0; i < m; ++ i)
			printf("cnt[%d] = %d\n", i, cnt[i]);*/
		//sort(mod, mod + n);
		/*for(int i = 0; i < n; ++ i)
			++ cnt[mod[i]];*/
		for(int i = 0; i < m; ++ i){
			if(cnt[i] >= k){
				pos = i;
				break;
			}
		}
		if(pos == INF){
			printf("No\n");
			continue;
		}
		printf("%d: ", n);
		printf("Yes\n");
		int ans[maxn] = {0}, p = 0;;
		for(int i = 0; i < n; ++ i){
			if(mod[i] == pos)
				ans[p++] = a[i];
			if(p >= k)break;
		}
		printf("%d", ans[0]);
		for(int i = 1; i < p; ++ i)
			printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}