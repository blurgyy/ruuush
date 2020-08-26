#include <cassert>
#include <cstdio>
#include <cstring>
const int maxdigits = 50;
const int maxnum    = 100;

int  a[maxnum + 10][maxdigits + 10];
int  ans[maxdigits + 10];
char s[maxdigits + 10];

void init() {
    memset(a, 0, sizeof(a));
    memset(ans, 0, sizeof(ans));
}

int main() {
    freopen("in.in", "r", stdin);
    int n = 0;
    while (~scanf("%s", s)) {
        int len = strlen(s);
        assert(len == maxdigits);
        for (int i = maxdigits - 1; i >= 0; --i) {
            a[n][maxdigits - 1 - i] = s[i] - '0';
        }
        ++n;
    }
    // for (int i = 0; i < maxnum; ++i) {
    // for (int d = maxdigits - 1; d >= 0; --d) {
    // printf("%d", a[i][d]);
    // }
    // printf("\n");
    // }
    for (int i = 0; i < maxdigits; ++i) {
        for (int id = 0; id < maxnum; ++id) {
            ans[i] += a[id][i];
        }
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }

    int topdigit = maxdigits;
    while (ans[topdigit] > 10) {
        ans[topdigit + 1] = ans[topdigit] / 10;
        ans[topdigit] /= 10;
        // ans[topdigit++] /= 10; // ??????
        ++topdigit;
    }

    for (int i = topdigit; i >= 0; --i) {
        printf("%d", ans[i]);
    }
    printf("\n");
    for (int i = topdigit; i > topdigit - 10; --i) {
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 22 2020
