#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5010;
const int inf = 0x3f3f3f3f;
const int nons = -1;

int T, n, m;
int s[maxn];
int rep[maxn<<1];
int ans[maxn][maxn];
int p[maxn];
int pref[maxn], suf[maxn];
int rad[maxn<<1];

bool check(int l, int r){
	if(l > r)return true;
	return l + r + rad[l+r] > r + r;
}

#define maxn 5010
//int rad[maxn<<1];
int manacher(int *x, int l){      //@ret (int)length of the longest palindrome in string X
    int ret = -1;
    int len = l * 2 + 1;
    int s[maxn<<1] = {0};
    memset(pref, 0, sizeof(pref));
    memset(suf, 0x3f, sizeof(suf));
    for(int i = 1; i <= len; ++ i){
        if(i & 1){
            s[i] = nons;
        }
        else {
            s[i] = x[i/2];
        }
    }
    int pos = 0, maxr = 0;
    for(int i = 1; i <= len; ++ i){
        if(i < maxr){
            rad[i] = min(rad[pos-i+pos], maxr - i);
        }
        else {
            rad[i] = 1;
        }
        while(i - rad[i] > 0 && i + rad[i] <= len && s[i-rad[i]] == s[i+rad[i]]){
            rad[i] ++;
        }
        if(i + rad[i] - 1 > maxr){
            maxr = i + rad[i] - 1;
            pos = i;
        }
        ret = max(ret, rad[i] - 1);
    }
    return ret;
}
#undef maxn

int main(){
	scanf("%d", &T);
	while(T --){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++ i){
			scanf("%d", s + i);
		}
		memset(p, 0, sizeof(p));

		for(int i = 1; i < n; ++ i){
			int tot = 0;
			for(int j = 0; i - j >= 1 && i + j + 1 <= n; ++ j){
				rep[++tot] = s[i-j];
				rep[++tot] = s[i+j+1];
			}
			// for(int i = 1; i <= tot; ++ i){
			// 	printf("%d%c", rep[i], " \n"[i==tot]);
			// }
			manacher(rep, tot);
			int len = tot * 2 + 1;
			for(int j = 3; j <= len; j += 2){
				if(rad[j] == j){
					pref[j-1] = j - 1;
				}
				int mir = (j + rad[j] - 1) / 2;
				if(suf[mir] > j / 2){
					suf[mir] = j / 2;
				}
			}
			for(int j = 1; j <= tot; ++ j){
				pref[j] = max(pref[j], pref[j-1]);
			}
			for(int j = tot; j >= 1; -- j){
				suf[j] = min(suf[j], suf[j+1]);
			}
			for(int j = 1; j <= tot; ++ j){
				if(suf[j] >= j){
					suf[j] = 0;
				}
				else {
					suf[j] = (j - suf[j]) * 2;
				}
			}
			for(int j = 2; j <= tot; j += 2){
				if(j == pref[j]){
					ans[j/2][p[j/2]++] = i - j/2 + 1;
				}
				else if(check(pref[j] + 1, j)){
					// printf("(%d, %d), i = %d, tot = %d\n", pref[j]+1, j, i, tot);
					ans[j/2][p[j/2]++] = i - j/2 + 1;
				}
				else if(check(1, j - suf[j])){
					ans[j/2][p[j/2]++] = i - j/2 + 1;
				}
				//if(check(pref[j] + 1, j)){
				//	// printf("pref(pref[%d] = %d)\n", j, pref[j]);
				//	ans[j/2][p[j/2]++] = i - pref[j]/2 + 1;
				//	printf("pans(pref[%d] = %d)\n", j, pref[j]);
				//}
				//else if(check(1, j - suf[j])){
				//	// printf("suf(suf[%d] = %d)\n", j, suf[j]);
				//	ans[j/2][p[j/2]++] = i - tot/2 + 1;
				//	printf("sans(suf[%d] = %d, %d)\n", j, suf[j], tot);
				//}
			}
		}
		// printf("...\n");
		int x, y;
		x = y = 0;
		for(int i = 1; i <= n; ++ i){
			y += !!(p[i]);
			x += p[i];
		}
		printf("%d %d\n", x, y);
		for(int i = 1; i <= n; ++ i){
			if(p[i]){
				printf("%d %d ", i*2, p[i]);
				for(int j = 0; j < p[i]; ++ j){
					printf("%d%c", ans[i][j], " \n"[j==p[i]-1]);
				}
			}
		}
	}

	return 0;
}