#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int  T, n;
char s[maxn];
int  cnt, bel[maxn];

void preinit() {
    cnt = 0;
    memset(bel, -1, sizeof(bel));
}

void postinit() {
    cnt = 0;
    for(int i = 0; i < n; ++ i) {
        bel[i] = -1;
    }
}

int main() {
    scanf("%d", &T);
    preinit();
    while (T--) {
        scanf("%d%s", &n, s);
        for (int i = 0; i < n; ++i) {
            if (bel[i] != -1) {
                continue;
            }
            int now = s[i] - '0';
            bel[i]  = ++cnt;
            for (int j = i + 1; j < n; ++j) {
                if (bel[j] != -1) {
                    continue;
                }
                if (s[j] - '0' == 1 - now) {
                    now    = s[j] - '0';
                    bel[j] = cnt;
                    // printf("bel[%d] = %d\n", j, cnt);
                }
            }
        }
        printf("%d\n", cnt);
        for (int i = 0; i < n; ++i) {
            printf("%d%c", bel[i], i == n - 1 ? '\n' : ' ');
        }
        postinit();
    }
    return 0;
}

// Author: Blurgy
// Date:   Aug 11 2020
