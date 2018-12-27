#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000010;
const int mod = 10007;

int T, n;
char s[maxn];
int Next[maxn];

void Get_next(){
	int i = 0, j = -1;
	memset(Next, 0, sizeof(Next));
	Next[0] = -1;
	while(i < n){
		/*if(j == -1 || s[i] == s[j]){
			++ i, ++ j;
			if(s[i] == s[j])
				Next[i] = Next[j];
			else Next[i] = j;
		}*/
        if(j == -1 || s[i] == s[j])
            Next[++i] = ++ j;
		else j = Next[j];
	}
}

void out(){
	for(int i = 0; i <= n; ++ i)
		printf("%d ", Next[i]);
	printf("\n");
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%s", &n, s);
		Get_next();
		out();
	}
	return 0;
}