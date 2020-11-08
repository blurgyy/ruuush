#include <bits/stdc++.h>
using namespace std;

char const *ch = "0123456789";

int T, k, X;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &k, &X);
        long long base = k;
        int       len  = 1;
        for (len = 1;; ++len) {
            if (X <= base) {
                break;
            }
            X -= base;
            base *= k;
        }
        string ans = "";
        --X;
        while (X) {
            ans = ch[10 - k + X % k] + ans;
            X /= k;
        }
        for (int i = 0; i + ans.size() < len; ++i) {
            cout << ch[10 - k];
        }
        cout << ans << endl;
    }
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Nov 01 2020
