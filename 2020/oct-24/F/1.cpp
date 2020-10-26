#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
        k >>= 1;
    }
    return ret;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

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
    printf("(%d, %d) / %d : %lld\n", left, right, d, ret);
    return ret;
}

int main() {
    freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while (T--) {
        // // test fast pow
        // scanf("%lld%lld", &n, &k);
        // printf("%lld\n", fp(n, k));
        // continue;

        // test cnt
        // int l, r, d;
        // scanf("%d%d%d", &l, &r, &d);
        // printf("%lld\n", cnt(l, r, d));
        // continue;

        ll ans  = 0;
        ll minx = INT_MAX + 1ll;
        ll maxx = -1;
        scanf("%lld%lld", &n, &k);
        if (n == 1) {
            printf("%lld\n", n);
            continue;
        }
        for (ll x = 2; fp(x, k) <= n; ++x) {
            ll left  = fp(x, k);
            ll right = fp(x, k + 1);
            if (left > n) {
                break;
            }
            minx = min(minx, x);
            maxx = max(maxx, x);
            ans += cnt(left, min(n, right), x);
            for (ll y = x - 1; y >= 2; --y) {
                // ll nleft  = fp(y, k);
                ll nright = fp(y, k + 1);
                if (left > nright) {
                    break;
                }
                // ans -= cnt(nright, min(n, left + 1), x * y / gcd(x, y));
                ans -= cnt(left, min(n, nright), x * y / gcd(x, y));
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Oct 24 2020
