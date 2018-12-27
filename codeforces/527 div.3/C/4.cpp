#include <bits/stdc++.h>
using namespace std;
const int maxn = 210;

int n;
struct NODE{
	char op[maxn];
	int id, len;
	void calc(){len = strlen(op);}
}a[maxn];
char s[maxn];
bool ans[maxn];

void uniform(char *x, char *y){
	int len = strlen(x);
	for(int i = 1; i < len; ++ i){
		if(x[i] != y[i-1]){
			swap(x, y);
		}
	}
}

bool operator< (NODE a, NODE b){
	return a.len < b.len;
}

bool ispref(char *s, char *x){
	int lenx = strlen(x);
	for(int i = 0; i < lenx; ++ i){
		if(s[i] != x[i]) return false;
	}
	return true;
}

int main(){
	// scanf("%s", s);
	// printf("len = %d\n", strlen(s));
	while(~scanf("%d", &n)){
		int tot = (n-1) * 2;
		for(int i = 1; i <= tot; ++ i){
			scanf("%s", a[i].op);
			a[i].calc();
			a[i].id = i;
		}
		sort(a+1, a+1 + tot);
		char *pref = a[tot].op;
		char *suf = a[tot-1].op;
		uniform(pref, suf);
		strcpy(s, pref);
		s[n-1] = suf[n-2];
		s[n] = 0;
		if(n == 67) printf("s = %s\n", s);
		for(int i = 1; i <= tot; i += 2){
			ans[a[i].id] = ispref(s, a[i].op);
			ans[a[i+1].id] = !ans[a[i].id];
		}
		for(int i = 1; i <= tot; ++ i){
			printf("%c", ans[i] ? 'S' : 'P');
		}
		printf("\n");
	}
	return 0;
}