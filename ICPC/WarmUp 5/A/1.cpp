#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;
const char ans[2][50] = {"This problem may be somewhat difficult.", "This is an easy problem."};

int T;
int n, m;
char prefix[20][maxn], title[20][maxn];
int Case = 0;

bool check(int index){
	for(int i = 0; i < n; ++ i){
		int len = strlen(prefix[i]);
		int j;
		for(j = 0; j < len; ++ j)
			if(prefix[i][j] != title[index][j])break;
		if(j == len)return true;
	}
	return false;
}

int main(){
	scanf("%d", &T);
	while(T--){
		memset(prefix, 0, sizeof(prefix));
		memset(title, 0, sizeof(title));
		scanf("%d%d", &n, &m);
		getchar();
		int len;
		for(int i = 0; i < n; ++ i){
			gets(prefix[i]);
			
			
		}
		for(int i = 0; i < m; ++ i){
			gets(title[i]);
			//len = strlen(title[i]);
			//title[i][len-1] = 0;
		}
		if(Case)printf("\n");
		printf("Case #%d:\n", ++ Case);
		for(int i = 0; i < m; ++ i)
			printf("%s\n", ans[check(i)]);
	}
	return 0;
}

/**

2
5 5
A
Advice
Boring
Detect
Enter
Advice from Jad
Boring Homework
Completely Difficult
Detection of zerg
Entering the Matrix
2 5
Google
Ju
Fudan University Local Contest
Google Earth
Hidden tiles
Illumination
Junk Mail Filter

*/