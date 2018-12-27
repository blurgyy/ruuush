/////bzoj4962
//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5010;
const int nons = -1;

int T, n, m;
int s[maxn];
int tot;
int rep[maxn];
int rad[maxn<<1];
int ans[maxn][maxn];
int p[maxn];

inline bool check(int l, int r){    ///s[l,r] is a palindrome ? 1 : 0;
    if(l > r)return true;
    printf("lhs = %d, rhs = %d\n", l+r+rad[l+r], r+r);
    return l + r + rad[l+r] > r + r;
}

#define maxn 5010
//int rad[maxn<<1];
int manacher(int *x, int l){      //@ret (int)length of the longest palindrome in string X
    int ret = -1;
    int len = l * 2 + 1;
    int s[maxn<<1] = {0};
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
        // manacher(s, n);
        // int l, r;
        // while(~scanf("%d%d", &l, &r)){
            // printf("%s", check(l, r) ? "yes\n" : "no\n");
        // }

        for(int i = 1; i < n; ++ i){
            for(int j = 0; i - j >= 1 && i + j + 1 <= n; ++ j){
                rep[++tot] = s[i-j];
                rep[++tot] = s[i+j+1];
            }
            manacher(rep, tot);
            int len = (tot << 1) + 1;
            for(int k = 3; k <= len; k += 2){
                if(rad[k] == k){
                    // ans ++;
                    ans[k/2][p[k/2]++] = i - k/2 + 1;
                    // printf("ans(%d) = %d\n", k/2, i - k/2 + 1);
                    for(int stop = k * 2 - 1, ii = stop + 2; ii <= len; ii += 2){
                        if(rad[ii] == ii - stop + 1){
                            //printf("k = %d, rad[%d] = %d\n", k, ii, rad[ii]);
                            //ans ++;
                            int curans = (rad[ii] + rad[k] - 2) / 2;
                            //printf("curans = %d !!!!!!!!!!\n", curans);
                            ans[curans][p[curans]++] = i - curans + 1;
                        }
                    }
                }
            }
            //printf("mid = (%d) ", i);
            for(int i = 1; i <= (tot<<1) + 1; ++ i){
                //printf("%d ", rad[i]);
            }
            //printf("\n");
            // if(preflen || suflen){
            //    printf("preflen = %d, suflen = %d\n", preflen, suflen);
            // }
        }
        // for(int i = 1; i <= n<<1; ++ i){
        //     //printf("rad[%d] = %d\n", i, rad[i]);
        // }
        int x = 0, y = 0;
        for(int i = 1; i <= n; ++ i){
            if(p[i]){
                y ++;
                x += p[i];
            }
        }
        printf("%d %d\n", x, y);
        for(int i = 1; i <= n; ++ i){
            if(p[i]){
                printf("%d %d ", i * 2, p[i]);
                for(int j = 0; j < p[i]; ++ j){
                    printf("%d%c", ans[i][j], " \n"[j==p[i]-1]);
                }
            }
        }
    }
    return 0;
}
