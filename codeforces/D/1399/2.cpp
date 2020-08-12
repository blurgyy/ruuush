#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int  T, n;
char s[maxn];
int  ans, bel[maxn];
int  nxtch[maxn];

void init() {
    ans = 0;
    memset(bel, -1, sizeof(bel));
    memset(nxtch, -1, sizeof(nxtch));
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, s);
        init();
        for (int i = 1, last = 0; i <= n; ++i) {
            if (s[i] != s[last]) {
                for (int j = last; j < i; ++j) {
                    nxtch[j] = i;
                }
                last = i;
            }
        }
        for (int i = 0; i < n; i = nxtch[i]) {
            for (int j = i; j < nxtch[i]; ++j) {
                bel[j] = j - i + 1;
                ans = max(ans, bel[j]);
            }
        }
        printf("%d\n", ans);
        for (int i = 0; i < n; ++i) {
            printf("%d%c", bel[i], i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

// Author: Blurgy
// Date:   Aug 12 2020
