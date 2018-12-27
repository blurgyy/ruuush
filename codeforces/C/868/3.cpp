//Thee most bruute method this iss...

#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int n, k, minp;
int know[maxn][5], cnt[5], state[2][5];
set<int> rec;

bool dfs(set<int>::iterator iter = rec.begin(), int count = 1){
	if(count > minp)return false;
	int index = *iter;
	++ iter;
	for(int i = 1; i <= k; ++ i)
		++ state[know[index][i]][i];
	int tmp;
	for(tmp = 1; tmp <= k; ++ tmp)
		if(state[0][tmp] < state[1][tmp])break;
	if(tmp == k+1)return true;
	for(; iter != rec.end(); ++ iter){
		if(dfs(iter, count + 1))return true;
	}
	for(int i = 1; i <= k; ++ i)
		-- state[know[index][i]][i];
	return false;
}

void init(){
	minp = INF;
	rec.clear();
	memset(know, 0, sizeof(know));
	memset(cnt, 0, sizeof(cnt));
	memset(state, 0, sizeof(state));
}

int main(){
	while(~scanf("%d%d", &n, &k)){
		init();
		for(int i = 1; i <= n; ++ i){
			for(int j = 1; j <= k; ++ j){
				scanf("%d", know[i] + j);
				if(know[i][j])continue;
				rec.insert(i);
				++ cnt[j];
			}
		}
		for(int i = 1; i <= k; ++ i)
			minp = min(minp, cnt[i]<<1);
		if(dfs())printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}