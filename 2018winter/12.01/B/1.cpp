#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int T;
int n;
int a[maxn], pos[maxn];

int main(){
	scanf("%d", &T);
	priority_queue<int> que;
	while(T --){
		while(!que.empty()) que.pop();
		// que.push(inf);
		scanf("%d", &n);
		for(int i = 1, x; i <= n; ++ i){
			scanf("%d", a + i);
			pos[a[i]] = i;
		}
		bool ans = true;
		for(int i = 1; i <= n; ++ i){
			// if(que.empty())continue;
			int cur = que.size() ? -que.top() : inf;
			// printf("cur1 = %d\n", cur);
			if(cur == pos[a[i]]){
				que.pop();
				continue;
			}
			if(a[i] & 1){
				if(cur < pos[a[i]+1]){
					ans = false;
					break;
				}
				if(a[i]+1 <= n)que.push(-(pos[a[i]+1]));
			}
			else {
				if(cur < pos[a[i]-1]){
					ans = false;
					break;
				}
				if(a[i]-1 >= 1)que.push(-(pos[a[i]-1]));
			}
		}
		if(ans == false){
			printf("No\n");
			continue;
		}
		for(int i = 1; i <= n; ++ i){
			// if(que.empty()) continue;
			int cur = que.size() ? -que.top() : inf;
			// printf("cur2 = %d\n", cur);
			if(cur == pos[a[i]]){
				que.pop();
				continue;
			}
			if(a[i] & 1){
				if(cur < pos[a[i]-1]){
					ans = false;
					break;
				}
				if(a[i]-1 >= 1)que.push(-(pos[a[i]-1]));
			}
			else {
				if(cur < pos[a[i]+1]){
					ans = false;
					break;
				}
				if(a[i]+1 <= n)que.push(-(pos[a[i]+1]));
			}
		}
		if(ans) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}