#include <cstdio>
typedef long long ll;
const double      eps = 1e-7;

ll square(ll x) { return x * x; }
ll cubic(ll x) { return x * x * x; }

// f(x) = \Sigma_{i=1}^{x}x^2
ll f(ll x) {
    return 1.0 / 3 * cubic(x) + 1.0 / 2 * square(x) + 1.0 / 6 * x + eps;
}

// g(x) = {\Sigma_{i-1}^{x}x}^2
ll g(ll x) { return square((1 + x) * x / 2); }

ll solve(ll x) { return g(x) - f(x); }

int main() {
    ll x;
    while (scanf("%lld", &x)) {
        printf("f(%lld) = %lld, g(%lld) = %lld\n", x, f(x), x, g(x));
        printf("diff = %lld\n", solve(x));
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 21 2020
