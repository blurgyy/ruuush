///#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
const int maxn = 1000010;

int T, Next[maxn];
char s[maxn], p[maxn];

void Get_Next(){
	memset(Next, 0, sizeof(Next));
	int len = strlen(p);
	Next[0] = -1;
	int j = 0, k = -1;
	while(j < len-1){
		if(k == -1 || p[j] == p[k]){
			++j;
			++k;
			Next[j] = k;
		}
		else k = Next[k];
	}
}

int KMP(){
	int slen = strlen(s);
	int plen = strlen(p);
	int i = 0, j = 0, ans = 0;
	while(i < slen){
		if(j == -1 || s[i] == p[j]){
			++ i;
			++ j;
		}
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
		scanf("%s%s", p, s);
		Get_Next();
		int ans = 0;
		int i = 0, j = 0;
		int slen = strlen(s);
		int plen = strlen(p);
		ans = KMP();
		/*while(i < slen){
			if(j == -1 || s[i] == p[j]){
				i++, j++;
			}
			else j = Next[j]; 
			if(j == plen){
				ans++;
				j = Next[j];
			}
		}*/
        printf("%d\n", ans);
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