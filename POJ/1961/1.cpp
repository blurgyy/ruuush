#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000010;

char s[maxn];
int Next[maxn], len;
int Case = 0;

void Get_next(){
	int i = 0, j = -1;
	memset(Next, 0, sizeof(Next));
	Next[0] = -1;
	while(i < len){
		if(j == -1 || s[i] == s[j])
			Next[++i] = ++j;
		else j = Next[j];
	}
}

int main(){
	while(~scanf("%d", &len) && len){
		scanf("%s", s);
		Get_next();
		printf("Test case #%d\n", ++ Case);
		for(int i = 2; i <= len; ++i)
			if(i % (i - Next[i]) == 0 && i / (i - Next[i]) > 1)
				printf("%d %d\n", i, i/(i-Next[i]));
		printf("\n");
	}
	return 0;
}