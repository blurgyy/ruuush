#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 400010;

struct Node{
	int to;
	int ne;
};
Node node[maxn];
int head[maxn];
int top;
int n;
ll sum_all;
ll a[maxn];
ll sum[maxn];
ll ans[maxn];

void add(int  from, int to){
	node[top].to = to;
	node[top].ne = head[from];
	head[from] = top;
	top ++;
}

ll dfs(int now = 1, int prv = -1){
	sum[now] = a[now];
	for(int i = head[now]; i != -1; i = node[i].ne){
		int nxt = node[i].to;
		if(nxt == prv) continue;
		sum[now] += dfs(nxt, now);
	}
	return sum[now];
}

void dfs_(int now = 1, int prv = -1){
	for(int i = head[now]; i != -1; i = node[i].ne){
		int nxt = node[i].to;
		if(nxt == prv) continue;
		ans[1] += sum[nxt];
		dfs_(nxt, now);
	}
}

void _dfs(int now = 1, int prv = -1){
	for(int i = head[now]; i != -1; i = node[i].ne){
		int nxt = node[i].to;
		if(nxt == prv) continue;
		ans[nxt] = ans[now] - sum[nxt] + (sum_all - sum[nxt]);
		_dfs(nxt, now);
	}
}

void ini(){
	top = 0;
	memset(head, -1, sizeof(head));
}
void init(){
	ini();
	memset(sum, 0, sizeof(sum));
	memset(ans, 0, sizeof(ans));
}

int main(){
	while(~scanf("%d", &n)){
		init();
		for(int i = 1; i <= n; ++ i){
			scanf("%d", a + i);
		}
		for(int i = 1, u, v; i < n; ++ i){
			scanf("%d%d", &u, &v);
			add(u, v);
			add(v, u);
		}
		sum_all = dfs();
		dfs_();
		_dfs();
		ll maxx = -1;
		for(int i = 1; i <= n; ++ i){
			// printf("[%d] : %I64d\n", i, ans[i]);
			maxx = max(maxx, ans[i]);
		}
		printf("%I64d\n", maxx);
	}
	return 0;
}