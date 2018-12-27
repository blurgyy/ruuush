///WTF WHAT'S THE DIFFERENCE BETWEEN THIS AND THAT "1.CPP"
///F**K
///I'LL TRY RE WRITE THIS PROBLEM
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
const int maxn = 1000010;

int T;
int tlen, plen, Next[maxn];
char text[maxn], pat[maxn];

void Get_Next(){
	int i = 0, j = -1;
	Next[0] = -1;
	while(i < plen){
		if(j == -1 || pat[i] == pat[j])
			Next[++i] = ++j;
		else j = Next[j];
	}
}

int KMP(){
	Get_Next();
	int i = 0, j = 0;
	int ans = 0;
	while(i < tlen){
		if(j == -1 || text[i] == pat[j])
			++ i, ++ j;
		else j = Next[j];
		if(j == plen){
			++ ans;
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