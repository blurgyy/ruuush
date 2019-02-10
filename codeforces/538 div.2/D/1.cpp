#include <bits/stdc++.h>
using namespace std;
const int maxn = 5010;
const int inf = 0x3f3f3f3f;

int n;
int a[maxn];

bool check(){
	int final = a[0]
	for(int i = 0; i < n; ++ i)
		if(a[i] != final) return false;
	return true;
}

int upd(int c){
	while(!check()){
		
	}
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; ++ i){
			scanf("%d", a + i);
		}
		int final = a[0];
		ans = min(ans, upd(final));
		printf("%d\n", ans);
	}
	return 0;
}
