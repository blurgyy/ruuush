#include <bits/stdc++.h>
using namespace std;
int const maxn = 1010;
int const maxk = 20;

int  n, k, t;
char s[maxn];
int  ans[maxn][maxk];
int  start[maxk];

int value(int prv, int now, int len) {
    int overlap = max(0, min(len + 1, prv + t) - now);
    int endlap  = max(0, now + t - 1 - len);
    int ret     = t - overlap - endlap;
    return ret;
}

int main() {
    // freopen("in2.in", "r", stdin);
    while (~scanf("%d%d%d%s", &n, &k, &t, s + 1)) {
        // memset(ans, 0, sizeof(ans));
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxk; ++j) {
                ans[i][j] = -maxn * 4;
            }
        }
        memset(start, 0, sizeof(start));
        int aans = 0;
        for (int j = 1; j <= k; ++j) {
            for (int i = start[j - 1] + 1; i <= n; ++i) {
                if (s[i] == '1') {
                    if (start[j] == 0) {
                        start[j] = i;
                    }
                    if (j == 1) {
                        ans[i][j] = min(t, n - i + 1);
                    } else {
                        for (int l = start[j - 1]; l < i; ++l) {
                            if (s[l] == '1') {
                                ans[i][j] =
                                    max(ans[i][j],
                                        ans[l][j - 1] + value(l, i, n));
                            }
                        }
                    }
                    aans = max(aans, ans[i][j]);
                }
            }
        }
        // printf("start:");
        // for (int i = 1; i <= k; ++i) {
        // printf("%d ", start[i]);
        // }
        // printf("\n");
        printf("%d\n", n - aans);
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Nov 08 2020, 15:51 [CST]
