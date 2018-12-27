#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;

int n;
char s[maxn];
struct node{
	char op[maxn];
	int len;
}a[maxn];

bool prefix(char *x){
	char tmpch = s[n-1];
	s[n-1] = 0;
	bool ret = (strcmp(s, x) == 0);
	s[n-1] = tmpch;
	s[n] = 0;
	return ret;
}

int main(){
	while(~scanf("%d", &n)){
		memset(s, 0, sizeof(s));
		int tot = (n-1) * 2;
		bool first = true;
		for(int i = 0; i < tot; ++ i){
			scanf("%s", a[i].op);
			a[i].len = strlen(a[i].op);
			if(a[i].len == n-1){
				if(first){
					first = false;
					strcpy(s, a[i].op);
				}
				else {
					s[n-1] = a[i].op[n-2];
				}
			}
		}
		char o;
		for(int i = 0, cp = 0, cs = 0; i < tot; ++ i){
			if(prefix(a[i].op)){
				if(cp == n-1){
					++ cs;
					o = 'S';
				}
				else {
					++ cp;
					o = 'P';
				}
			}
			else {
				if(cs == n-1){
					++ cp;
					o = 'P';
				}
				else {
					++ cs;
					o = 'S';
				}
			}
			printf("%c", o);
		}
		printf("\n");
	}
	return 0;
}