#include <cmath>
#include <cstdio>
typedef long long ll;
const ll          maxn = 100010;

constexpr ll trinum(ll x) { return (x * x + x) / 2; }
ll           divcount(ll x) {
    ll ret = 0;
    ll top = sqrt(x);
    for (int i = 1; i <= top; ++i) {
        if (x % i == 0) {
            ++ret;
            if (x / i != i) {
                ++ret;
            }
        }
    }
    return ret;
}

int main() {
    // ll x;
    // while(~scanf("%lld", &x)) {
    // printf("%lld has %lld divisor(s)\n", x, divcount(x));
    // }
    for (ll i = 1; i < maxn; ++i) {
        if (divcount(trinum(i)) > 500) {
            printf("ans is %lld\n", i);
            break;
        }
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 22 2020
