#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
int const              maxn = 40010;

int         a, k;
int         ans, allsum;
vector<pii> pk;

void pm(int val) {
    for (int p = 2; val > 1; ++p) {
        if (val % p == 0) {
            pii now = pii(p, 0);
            while (val % p == 0) {
                now.second++;
                val /= p;
                allsum += p;
            }
            pk.push_back(now);
        }
    }
}

int ipow(int x, int k) {
    int ret = 1;
    while (k--) {
        ret *= x;
    }
    return ret;
}

void dfs(int cur = 1, int cursum = 0, int pind = 0) {
    if (pind >= pk.size()) {
        return;
    }
    int nowp = pk[pind].first;
    int cnt  = pk[pind].second;
    for (int i = 0; i <= cnt; ++i) {
        int nval = ipow(nowp, i);
        int nsum = cursum + nowp * i;
        if (cur * nval >= k) {
            ans = min(ans, cursum + nowp * max(0, i - 1));
            return;
        }
        dfs(cur * nval, nsum, pind + 1);
    }
}

void init() {
    pk.clear();
    ans    = 0x7fffffff;
    allsum = 0;
}

int main() {
    // freopen("in.in", "r", stdin);
    while (~scanf("%d%d", &a, &k)) {
        init();
        pm(a);
        dfs();
        printf("%d\n", allsum - min(allsum, ans));
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Nov 08 2020, 14:38 [CST]
