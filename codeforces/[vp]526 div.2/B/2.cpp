#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const size_t maxn = 100010;
const int mod = 1e9 + 7;

char s[maxn];
ll dp[maxn];

int main(){
	memset(dp, 0, sizeof(dp));
	while(~scanf("%s", s+1)){
		int len = strlen(s+1);
		int cnta = 0;
		for(int i = 1; i <= len; ++ i){
			cnta += s[i] == 'a';
		}
		for(int i = 1; i <= cnta; ++ i) dp[i] = 1;
		ll ans = cnta;

		int l = -1, r = 0;
		for(int i = 1, cur = 0, lasta = -1, lastb = -1; i <= len; ++ i){
			if(s[i] == 'a'){
				lasta = i;
				cur ++;
				if(l <= r){
					l = cur;
				}
			}
			if(s[i] == 'b'){
				if(lastb > lasta || cur == 0) continue;
				r = cur;
				lastb = i;
				addv = query(l, r);
				update(r+1, cnta, addv);
			}
		}
		printf("%lld\n", query(1, cnta));
	}
	return 0;
}