#include <cstdio>
typedef long long ll;
const int         maxn = 30;
const int         prob = 21;

ll ans[maxn][maxn];

bool inrange(int x) { return x >= 1 && x <= prob; }
bool inrange(int x, int y) { return inrange(x) && inrange(y); }

int main() {
    for (int i = 1; i <= prob; ++i) {
        for (int j = 1; j <= prob; ++j) {
            if (i == 1 && j == 1) {
                ans[i][j] = 1;
            } else {
                if (inrange(i - 1) && inrange(j - 1)) {
                    ans[i][j] = ans[i - 1][j] + ans[i][j - 1];
                } else if (inrange(i - 1)) {
                    ans[i][j] = ans[i - 1][j];
                } else if (inrange(j - 1)) {
                    ans[i][j] = ans[i][j - 1];
                }
            }
        }
    }
    for (int i = 1; i <= 3; ++ i) {
        for (int j = 1; j <= 3; ++ j) {
            printf("%lld ", ans[i][j]);
        }
        printf("\n");
    }
    printf("ans is %lld\n", ans[prob][prob]);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 23 2020
