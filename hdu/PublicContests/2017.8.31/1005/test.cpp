#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;

int n, q, query;
int num[maxn];
int ans[4];

int main(){
	while(~scanf("%d%d", &n, &q)){
		for(int i = 1; i <= n; i++)
			scanf("%d", num + i);
		while(q--){
			scanf("%d", &query);
			if(query != 1){
				ans[1] = ans[2] = ans[3] = num[1];
			}
			else{
				ans[1] = ans[2] = ans[3] = num[2];
			}
			for(int i = 1; i <= n; i++){
				if(i == query)continue;
				if(query != 1){
					if(i == 1)continue;
					ans[1] &= num[i];
					ans[2] |= num[i];
					ans[3] ^= num[i];
				}
				else{
					if(i == 2)continue;
					ans[1] &= num[i];
					ans[2] |= num[i];
					ans[3] ^= num[i];
				}
			}
			printf("%d %d %d\n", ans[1], ans[2], ans[3]);
		}
	}
	return 0;
}