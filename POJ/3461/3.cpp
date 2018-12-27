#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 1000010;

int T, Next[maxn];
char text[maxn], pat[maxn];
int tlen, plen;

void get_Next(){
	int i = 0, j = -1;
	Next[0] = -1;
	while(i < plen){
		if(j == -1 || pat[i] == pat[j])
			Next[++i] = ++j;
		else j = Next[j];
	}
}

int KMP(){
	get_Next();
	int ans = 0;
	int i = 0, j = 0;
	while(i < tlen){
		if(j == -1 || text[i] == pat[j])
			++ i, ++ j;
		else j = Next[j];
		if(j == plen){
			++ans;
			j = Next[j];
		}
	}
	return ans;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%s%s", pat, text);
		tlen = strlen(text);
		plen = strlen(pat);
		printf("%d\n", KMP());
	}
	return 0;
}

/**

3
BAPC
BAPC
AZA
AZAZAZA
VERDI
AVERDXIVYERDIAN

*/