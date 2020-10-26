#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int const maxn = 1000010;

int T;
int n;
struct Node {
    int         id;
    int         fa;
    int         dep;
    int         maxsub;
    vector<int> subid;
    vector<pii> sub; // first: max depth of subtree; second: id of child

    void ini() {
        id = fa = dep = maxsub = -1;
        subid.clear();
        sub.clear();
    }
    // bool operator<(Node const &rhs) { return maxsub < rhs.maxsub; }
} node[maxn];

/*****************************************************************/
inline char read() {
    static const int IN_LEN = 1000000;
    static char      buf[IN_LEN], *s, *t;
    if (s == t) {
        t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
        if (s == t)
            return -1;
    }
    return *s++;
}
template <class T> inline void read(T &x) {
    static char c;
    static bool iosig;
    for (c = read(), iosig = false; !isdigit(c); c = read()) {
        if (c == '-')
            iosig = true;
        if (c == -1)
            return;
    }
    for (x = 0; isdigit(c); c = read())
        x = (x + (x << 2) << 1) + (c ^ '0');
    if (iosig)
        x = -x;
}
/*****************************************************************/

// return max depth of sub-trees
int getdep(int now = 1, int from = 0) {
    int ret = node[now].dep;
    for (int &i : node[now].subid) {
        node[i].dep    = node[now].dep + 1;
        node[i].maxsub = getdep(i, now);
        ret            = max(ret, node[i].maxsub);
        node[now].sub.push_back(make_pair(node[i].maxsub, node[i].id));
        // node[now].sub.push_back(make_pair(node[i].dep, node[i].id));
    }
    sort(node[now].sub.begin(), node[now].sub.end());
    return ret;
}

int solve(int ans = 0, int now = 1, int from = 0) {
    for (int i = 0; i < node[now].sub.size(); ++i) {
        Node x = node[node[now].sub[i].second];
        ans    = solve(ans + 1, x.id, now);
        if (i == node[now].sub.size() - 1) {
            continue;
        }
        if (x.maxsub - node[now].dep < node[now].dep) {
            ans += x.maxsub - node[now].dep;
        } else {
            ans += node[now].dep;
        }
    }
    return ans;
}

void init() {
    for (int i = 0; i <= n; ++i) {
        node[i].ini();
    }
}

int main() {
    read(T);
    for (int ncase = 1; ncase <= T; ++ncase) {
        // Case #x: y
        read(n);
        init();
        node[1].id = 1;
        for (int i = 2, x; i <= n; ++i) {
            read(x);
            node[i].id = i;
            node[i].fa = x;
            node[x].subid.push_back(i);
        }
        node[1].dep = 0;
        getdep();
        printf("Case #%d: %d\n", ncase, solve());
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Oct 24 2020
