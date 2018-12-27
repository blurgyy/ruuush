#include <bits/stdc++.h>
using namespace std;
const int maxn = 410;

struct node{
	int id;
	char x[maxn];
	int len;
	bool operator< (node &rhs){
		return len < rhs.len;
	}
}a[maxn];
int n;
char s[maxn];
char ans[maxn];

bool prefix(char *x){
	int xlen = strlen(x);
	for(int i = 0; i < xlen; ++ i)
		if(s[i] != x[i]) return false;
	return true;
}

int main(){
	while(~scanf("%d", &n)){
		int tot = (n - 1) * 2;
		for(int i = 0; i < tot; ++ i){
			a[i].id = i;
			scanf("%s", a[i].x);
			a[i].len = strlen(a[i].x);
		}
		sort(a, a + tot);
		strcpy(s, a[tot-2].x);
		s[n-1] = a[tot-1].x[n-2];
		s[n] = 0;
		// printf("s = %s\n", s);
		for(int i = 0; i < tot; i += 2){
			if(prefix(a[i].x)){
				ans[a[i].id] = 'P';
				ans[a[i+1].id] = 'S';
			}
			else {
				ans[a[i].id] = 'S';
				ans[a[i+1].id] = 'P';
			}
		}
		ans[tot] = 0;
		printf("%s\n", ans);
	}
	return 0;
}