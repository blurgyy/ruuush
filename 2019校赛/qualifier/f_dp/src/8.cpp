#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

int T, len;
int pref[maxn];
int pmin[maxn];
int pmax[maxn];
char s[maxn];

int main(){
	pref[0] = 0;
	pmin[0] = 0;
	pmax[0] = 0;
	scanf("%d", &T);
	while(T --){
		scanf("%d%s", &len, s + 1);
		for(int i = 1; i <= len; ++ i){
			if(s[i] == 'A'){
				pref[i] = pref[i-1] + 1;
			}
			else if(s[i] == 'B') {
				pref[i] = pref[i-1] - 1;
			}
			pmin[i] = min(pmin[i-1], pref[i]);
			pmax[i] = max(pmax[i-1], pref[i]);
		}
		int minx = inf, maxx = -inf;
		for(int i = 1; i <= len; ++ i){
			minx = min(minx, pref[i] - pmax[i]);
			maxx = max(maxx, pref[i] - pmin[i]);
		}
		printf("%d\n", max(abs(minx), abs(maxx)));
	}
	return 0;
}
