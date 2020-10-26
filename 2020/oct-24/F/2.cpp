#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll const maxp = 1e9;

int T;
ll  n, k;

ll fp(ll x, ll k) {
    ll base = x;
    ll ret  = 1;
    while (k) {
        if (k & 1) {
            ret *= base;
        }
        base = base * base;
        if (base > maxp) {
            return -1;
        }
        k >>= 1;
    }
    return ret;
}

// range: [left, rignt)
ll cnt(int left, int right, int d) {
    int kl = left / d;
    int kr = right / d;
    if (left % d) {
        ++kl;
    }
    if (right % d == 0) {
        --kr;
    }
    ll ret = max(0, kr - kl + 1);
    return ret;
}

int main() {
    // freopen("in.in", "r", stdin);
    scanf("%d", &T);
    for (int ncase = 1; ncase <= T; ++ncase) {
        printf("Case #%d: ", ncase);
        ll ans  = 0;
        scanf("%lld%lld", &n, &k);
        if (k == 1) {
            printf("%lld\n", n);
            continue;
        }

        vector<ll> bars;
        for (ll i = 1;; ++i) {
            ll p = fp(i, k);
            if (p != -1 && p <= n) {
                bars.push_back(p);
            } else {
                break;
            }
        }
        bars.push_back(n + 1);
        for (int i = 1; i < bars.size(); ++i) {
            ans += cnt(bars[i - 1], bars[i], i);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Oct 24 2020
