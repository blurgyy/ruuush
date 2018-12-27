#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000010;

char s[maxn];
int len, Next[maxn];

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
	while(~scanf("%s", s) && strcmp(s, ".")){
		len = strlen(s);
		Get_next();
		if(len % (len - Next[len]))
			printf("1\n");
		else printf("%d\n", len/(len-Next[len]));
	}
	return 0; 
}