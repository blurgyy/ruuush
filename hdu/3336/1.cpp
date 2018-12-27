#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200010;
const int mod = 10007;

char s[maxn];
int T;
int Next[maxn], len, ans;

void Get_Next(){
	int i = 0, j = -1;
	memset(Next, 0, sizeof(Next));
	Next[0] = -1;
	while(i < len){
		if(j == -1 || s[i] == s[j])
			Next[++i] = ++j;
		else j = Next[j];
	}
}

void out(){
	for(int i = 0; i < len; ++ i)
		printf("%d ", Next[i]);
	printf("\n");
}

int main(){
	while(~scanf("%d", &T)){
		while(T--){
			ans = 0;
			scanf("%d%s", &len, s);
			Get_Next();
			out();
			for(int pos = 0; pos <= len; ++ pos){
				int i = 0, j = -1;
				while(i < len){
					if(j == -1 || s[i] == s[j])
						++ j, ++ i;
					else j = Next[j];
					if(j == pos){
						++ ans;
						j = Next[j];
					}
				}
				if(ans > mod)ans %= mod;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}