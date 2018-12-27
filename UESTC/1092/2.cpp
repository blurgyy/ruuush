#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 110;
const ll INF = 0x3f3f3f3f;
const ll Prime = 998244353;
const ll mod = 1000000007;

char s[maxn];
ll idx[300];
ll Hash[200010];
int p;

void init(){
	p = 0;
	for(int i = 'a'; i <= 'z'; ++ i)
		idx[i] = ++p;
	for(int i = 'A'; i <= 'Z'; ++ i)
		idx[i] = ++p;
	for(int i = '0'; i <= '9'; ++ i)
		idx[i] = ++p;
	p = 0;
}

ll hashing(){
	ll ret = 0;
	for(int i = 0; i < 100; ++ i)
		ret += (idx[s[i]] * Prime + (i!=0) * idx[s[i-1]]) % mod;
	return ret;
}

int main(){
	int time = 5;
	init();
	while(time--){
		scanf("%s", s);
		Hash[p++] = hashing();
		//printf("Hash[] = %d\n", Hash[p-1]);
	}
	/*for(int i = 0; i < p; ++ i)
		printf("%lld\n", Hash[i]);*/
	int ans = 1;
	sort(Hash, Hash + p);
	//ans = unique(Hash, Hash + 20000) - Hash - 1;
	for(int i = 1; i < p; ++ i)
		if(Hash[i] != Hash[i-1])++ ans;
	printf("%d\n", ans);
	return 0;
}