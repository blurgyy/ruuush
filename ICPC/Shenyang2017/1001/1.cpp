#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;

int T, k, len;
int Next[maxn];
char s[maxn];

void Get_next(){
	int i = 0, j = -1;
	memset(Next, 0, sizeof(Next));
	Next[0] = -1;
	while(i < len){
		if(j == -1 || s[i] == s[j]){
			Next[++i] = ++ j;
		}
		else j = Next[j];
	}
}

void out(){
	for(int i = 0; i <= len; ++ i)
		printf("%d ", Next[i]);
	printf("\n");
}

int main()
{
	scanf("%d", &T);
	while(T--){
		scanf("%d%s", &k, s);
		len = strlen(s);
		Get_next();
		out();
	}
	return 0;
}
