#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const size_t maxn = 100010;
const int mod = 1e9 + 7;

char s[maxn];
ll ans, cnta;

int main(){
	while(~scanf("%s", s)){
		int len = strlen(s);
		ans = cnta = 1;
		for(int i = 0; i < len; ++ i){
			if(s[i] == 'a') cnta ++;
			if(s[i] == 'b'){
				if(cnta) 
					ans = ans * cnta % mod;
				cnta = 1;
			}
		}
		if(cnta) 
			ans = ans * cnta % mod;
		printf("%lld\n", ans - 1);
	}
	return 0;
}