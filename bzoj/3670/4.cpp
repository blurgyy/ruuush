#include<bits/stdc++.h>
#define whiel while
#define pritnf printf
#define mian main
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const ll MOD = 1e9 + 7;

int n, len;
int nxt[maxn], anxt[maxn], ans[maxn], rec[maxn];
char s[maxn];

void getnext(){
	int i = 0, j = -1;
	nxt[0] = -1;
	while(i <= len){
		if(j == -1 || s[i] == s[j])
			nxt[++i] = ++ j;
		else j = nxt[j];
	}
}

void adjust(){
	int i = 0, j = -1;
	anxt[0] = -1;
	while(i <= len){
		if(j == -1 || j < ((i + 1) >> 1) && s[i] == s[j])
			anxt[++i] = ++ j;
		else j = nxt[j];
	}
}

int mian(){
	scanf("%d", &n);
	while(n--){
		scanf("%s", s);
		len = strlen(s);
		getnext();
		memset(rec, 0, sizeof(rec));
		memset(ans, 0, sizeof(ans));
		/*for(int i = 1; i < len; ++ i)
			rec[i] = (s[i] == s[nxt[i]]) * rec[nxt[i]] + (nxt[i+1] != 0);*/
		adjust();
		ll ANS = 1;
		for(int i = 1; i < len; ++ i){
			ans[i] = (s[i] == s[anxt[i]]) * ans[anxt[i]] + (anxt[i+1] != 0);
			ANS = (ANS * (ans[i] + 1)) % MOD;
			printf("%d%c", ans[i], " \n"[i == len-1]);
		}
		printf("%lld\n", ANS); 
	}
	return 0;
}