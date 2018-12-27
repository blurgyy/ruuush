#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int T, Case = 0;
int nxt[maxn], ans[maxn];
char str[maxn];

void Get_next(char *s, int len){
	int i = 0, j = -1;
	while(i <= len){
		if(j == -1 || s[i] == s[j])
			nxt[++i] = ++ j;
		else j = nxt[j];
	}
}

int main(){
	memset(nxt, 0, sizeof(nxt));
	nxt[0] = -1;
	scanf("%d", &T);
	while(T--){
		memset(ans, 0, sizeof(ans));
		scanf("%s", str);
		int len = strlen(str), end = len;
		for(int i = 0; i < end; ++ i, -- len){
			Get_next(str + i, len);
			for(int j = len; j > 0; -- j){
				if(j % (j - nxt[j]))continue;
				int l = j - nxt[j], tmp = l;
				while(l <= j){
					int x = j / l;
					ans[x] = max(ans[x], x*l);
					l += tmp;
				}
			}
		}
		ans[1] = end;
		printf("Case #%d: ", ++ Case);
		printf("%d", ans[1]);
		for(int i = 2; i <= end; ++ i)
			printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}


