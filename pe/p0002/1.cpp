#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

long long fib[maxn];

int main() {
    fib[0] = fib[1] = 1;
    long long ans   = 0;
    for (int i = 2; i < maxn; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
        if (fib[i] >= 4000000) {
            break;
        }
        if ((fib[i] & 1) == 0) {
            ans += fib[i];
        }
    }
    // printf("ans * 2 = %lld, ans = %lld\n", ans, ans / 2);
    printf("ans = %d\n", ans);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 16 2020
