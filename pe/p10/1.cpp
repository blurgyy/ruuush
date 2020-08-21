#include <cstdio>
#include <cmath>
typedef long long ll;

bool check(ll x) {
    if (x == 1) {
        return false;
    }
    if (x == 2) {
        return true;
    }
    if (x & 1) {
        int top = sqrt(x) + 1;
        for (int i = 3; i <= top; ++i) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

int main() {
    ll ans = 0;
    ll top = 2000000;
    for (int i = 2; i < top; ++ i) {
        if (check(i)) {
            ans += i;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
