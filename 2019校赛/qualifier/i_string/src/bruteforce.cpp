#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N = 200010;

char ma[N];
char mb[N];

int main(int argc, char const *argv[])
{
	int ncase;
	int len1;
	int len2;
	LL ans;

	scanf("%d", &ncase);
	while(ncase --){
		ans = 0;
		scanf("%s%s", ma, mb);
		len1 = strlen(ma);
		len2 = strlen(mb);
		for(int i = 0; i < len2; i ++){
			for(int j = i; j < len2; j ++){
				int mark;

				mark = 0;
				if(j - i + 1 > len1){
					break;
				}
				for(int k = i; k <= j; k ++){
                    // printf("%d %d %d\n", i, j, k);
					if(mb[k] != ma[k - i]){
					    // printf("%c %c\n", mb[k], ma[k - i]);
						mark = 1;
						break;
					}
				}
				if(!mark){
                    // printf("%d %d\n", i, j);
					ans ++;
				}
			}
		}
		printf("%lld\n", ans);
	}

	return 0;
}
