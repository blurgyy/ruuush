#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 110;
const int INF = 0x3f3f3f3f;
const int MAXN = 20010;
const int Time = 20000;
const ll Prime = 1000000009;
const ll mod = 1000000007;

char s[maxn];
ll Hash[maxn];
ll ans[MAXN];
int p;
int idx[300];

void init(){
	p = 0;
	for(int i = 'a'; i <= 'z'; ++ i)
		idx[i] = ++ p;
	for(int i = 'A'; i <= 'Z'; ++ i)
		idx[i] = ++ p;
	for(int i = '0'; i <= '9'; ++ i)
		idx[i] = ++ p;
	p = 0;
}

int main(){
	init();
	for(int j = 0; j < Time; ++ j){
		scanf("%s", s);
		for(int i = 1; i < 100; ++ i)
			Hash[i] = (Hash[i-1] * Prime + idx[s[i-1]]) % mod;
		ans[p++] = Hash[99];
		printf("%d\n", Hash[99]);
	}
	sort(ans, ans + p);
	printf("%d\n", unique(ans, ans + p) - ans);
	return 0;
}
