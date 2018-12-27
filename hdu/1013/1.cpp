#include<cstdio>
#include<cstring>
const int maxn = 100010;

char n[maxn];

int main(){
	while(~scanf("%s", n) && strcmp(n, "0")){
		int ans = 0;
		while(true){
			int len = strlen(n);
			for(int i = 0; i < len; ++ i)
				ans += n[i] - '0';
			if(ans < 10)break;
			int p = 0;
			while(ans){
				n[p++] = ans%10 + '0';
				ans /= 10;
			}
			n[p++] = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}