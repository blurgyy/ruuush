#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int T;
ll  n, k;

ll pow(ll x, ll k) {
    ll ret = 1;
    while (k--) {
        ret *= x;
    }
    return ret;
}

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
    scanf("%d", &T);
    // Case #x: y
    for (int ncase = 1; ncase <= T; ++ncase) {
        scanf("%lld%lld", &n, &k);
        if (k == 1 || k >= 31) {
            printf("Case #%d: %lld\n", ncase, n);
        } else {
            vector<ll> bars;
            for (ll i = 1;; ++i) {
                ll p = pow(i, k);
                if (p <= n) {
                    bars.push_back(p);
                } else {
                    break;
                }
            }
            ll ans = 0;
            bars.push_back(n + 1);
            for (int i = 1; i < bars.size(); ++i) {
                ans += cnt(bars[i - 1], bars[i], i);
            }
            printf("Case #%d: %lld\n", ncase, ans);
        }
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Oct 24 2020
