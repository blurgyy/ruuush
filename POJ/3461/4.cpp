///Emmm...
///Going to sleep..
///I have some work to do tomorrow
///I'll check the "1.cpp" tomorrow maybe..
///Does it affect the result if it's in a function or not..?
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000010;

int T, Next[maxn];
char text[maxn], pat[maxn];
int tlen, plen;

void GetNext(){
	int i = 0, j = -1;
	Next[0] = -1;
	while(i < plen){
		if(j == -1 || pat[i] == pat[j])
			Next[++i] = ++j;
		else j = Next[j];
	}
}

int KMP(){
	GetNext();
	int i = 0, j = 0;
	int ans = 0;
	while(i < tlen){
		if(j == -1 || text[i] == pat[j])
			++ i, ++ j;
		else j = Next[j];
		if(j == plen)
			++ ans, j = Next[j];
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