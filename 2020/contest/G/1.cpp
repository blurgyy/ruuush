#include <bits/stdc++.h>
using namespace std;
int const maxn = 10;

char a[maxn];
char m[maxn];
int  x, y;
int  cntm[10], cntn[10];

bool judge(char m[], char n[]) {
    memset(cntm, 0, sizeof(cntm));
    memset(cntn, 0, sizeof(cntn));
    int curx = 0;
    int cury = 0;

    for (int i = 0; i < 5; ++i) {
        cntm[m[i] - '0']++;
        cntn[n[i] - '0']++;
        cury += m[i] == n[i];
    }
    for (int i = 0; i < 10; ++i) {
        curx += min(cntm[i], cntn[i]);
    }
    return curx == x && cury == y;
}

int main() {
    while (~scanf("%s%d%d", a, &x, &y)) {
        int ans = 0;
        for (int i = 0; i < 100000; ++i) {
            sprintf(m, "%05d", i);
            ans += judge(m, a);
        }
        printf("%d\n", ans);
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Nov 08 2020, 15:07 [CST]
