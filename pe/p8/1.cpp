#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;
const int maxn = 100010;

char buf[maxn];
int  s[maxn];
bool invalid[maxn];
int  nlen;
ll ans;

ll calc(int x) {
    ll ret = 1;
    for (int i = x; i < x + 13; ++ i) {
        ret *= 1ll * s[i];
    }
    return ret;
}

void init() {
    memset(invalid, false, sizeof(invalid));
    nlen = 0;
    ans = -1;
}

int main() {
    init();
    while (~scanf("%s", buf)) {
        int len = strlen(buf);
        for (int i = 0; i < len; ++i) {
            s[nlen + i] = buf[i] - '0';
        }
        nlen += len;
    }
    for (int i = 0; i < nlen; ++i) {
        if (i == 0) {
            for (int j = i; j >= std::max(0, i - 12); --j) {
                if (invalid[j]) {
                    break;
                }
                invalid[j] = true;
            }
        }
    }

    for(int i = 0; i < nlen; ++ i) {
        if (! invalid[i]) {
            ans = std::max(ans, calc(i));
        }
    }
    printf("max ans = %lld\n", ans);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 21 2020
