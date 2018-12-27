#include <bits/stdc++.h>
using namespace std;
const int maxn = 210;

int n;
char s[maxn];
struct NODE{
	char op[maxn];
	int len;
	int id;
	bool ispref;
	void calc(){len = strlen(op);}
	bool operator< (const NODE &rhs){return len < rhs.len;}
	void check(){
		for(int i = 0; i < len; ++ i){
			if(s[i] != op[i]) {
				ispref = false;
				return;
			}
		}
		ispref = true;
	}
}a[maxn];
bool ans[maxn];

void get(char *x, char *y){
	int len = strlen(x);
	bool swapped = false;
	for(int i = 1; i < len; ++ i){
		if(x[i] != y[i-1]){
			swap(x, y);
			swapped = true;
			break;
		}
	}
	for(int i = 0; i < len; ++ i){
		s[i] = x[i];
	}
	s[n-1] = y[len-1];
	s[n] = 0;
	if(swapped) swap(x, y);
}

int main(){
	while(~scanf("%d", &n)){
		int tot = (n-1) * 2;
		for(int i = 1; i <= tot; ++ i){
			scanf("%s", a[i].op);
			a[i].calc();
			a[i].id = i;
		}
		sort(a+1, a+1 + tot);
		get(a[tot-1].op, a[tot].op);
		// if(s[0] == 'w' && n == 100) printf("%s\n", s);
		for(int i = 1; i <= tot; i += 2){
			a[i].check();
			ans[a[i].id] = a[i].ispref;
			ans[a[i+1].id] = !ans[a[i].id];
		}
		for(int i = 1; i <= tot; ++ i){
			if(ans[i]) printf("P");
			else printf("S");
		}
		printf("\n");
	}
	return 0;
}