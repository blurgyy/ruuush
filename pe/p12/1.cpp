#include <cmath>
#include <cstdio>

typedef long long ll;

ll bs(ll checkfunc(ll), ll calcfunc(ll), ll left, ll right, ll e) {
    // printf("bs(*, %lld, %lld, %lld)\n", left, right, e);
    if (left >= right) {
        return right;
    }
    ll mid = (left + right) / 2;
    if (e <= checkfunc(calcfunc(mid))) {
        return bs(checkfunc, calcfunc, left, mid, e);
    } else {
        return bs(checkfunc, calcfunc, mid + 1, right, e);
    }
}

constexpr ll trinum(ll n) { return (n * n + n) / 2; }

ll divisor_count(ll x) {
    ll ret = 0;
    ll top = sqrt(x);
    for (ll i = 1; i <= top; ++i) {
        if (x % i == 0) {
            ++ret;
            if (x / i != i) {
                ++ret;
            }
        }
    }
    printf("%lld has %lld divisor(s)\n", x, ret);
    return ret;
}

int main() {
    // ll x;
    // while(~scanf("%lld", &x)) {
    // printf("%lld has %lld divisor(s)\n", x, divisor_count(x));
    // }
    // return 0;
    printf("%lld\n", bs(divisor_count, trinum, 1, 999999, 500));
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 22 2020
