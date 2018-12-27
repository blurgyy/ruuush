#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n;
char s[maxn], ch[maxn];

int main(){
	scanf("%d", &n);
	getchar();
	while(n--){
		memset(ch, 0, sizeof(ch));
		gets(s);
		int len = strlen(s);
		int p = 0;
		for(int i = 0; i < len; ++ i){
			if(s[i] >= 'A' && s[i] <= 'Z'){//
				ch[p++] = s[i] + 32;
			}
			else if(s[i] >= 'a' && s[i] <= 'z'){
				ch[p++] = s[i];
			}
		}
		//printf("%s\n", ch);
		len = strlen(ch);
		bool ans = true;
		for(int i = 0; i < len/2; ++ i){
			if(ch[i] == ch[len-i-1])continue;
			ans = false;
			break;
		}
		if(ans)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}