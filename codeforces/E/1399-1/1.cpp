#include <bits/stdc++.h>
using namespace std;
typedef long long     ll;
typedef pair<ll, int> pii;
const int             maxn = 200010;

int t, n;
int u, v, w;
int leaves[maxn];
int value[maxn];
int ans;
ll  S;
struct Node {
    int w;
    int to;
    int ne;
};
Node node[maxn];
int  head[maxn];
int  top;

void add(int from, int to, int w) {
    // printf("Adding edge: (%d -> %d):%d\n", from, to, w);
    node[top].to = to;
    node[top].w  = w;
    node[top].ne = head[from];
    head[from]   = top;
    top++;
}

// for (int i = head[u]; i != -1; i = node[i].ne) {
// int nxt = node[i].to;
// /// 遍历
// }

void ini() {
    top = 0;
    memset(head, -1, sizeof(head));
}

int dfs(int now = 1, int prv = -1) {
    // printf("iterating %d-th node from %d-th node.\n", now, prv);
    bool isleaf = true;
    for (int i = head[now]; i != -1; i = node[i].ne) {
        int nxt = node[i].to;
        if (nxt == prv) {
            value[now] = node[i].w;
            continue;
        }
        isleaf = false;
        leaves[now] += dfs(nxt, now);
    }
    if (isleaf) {
        leaves[now] = 1;
    }
    return leaves[now];
}

ll total() {
    ll ret = 0;
    for (int i = 2; i <= n; ++i) {
        ret += 1ll * leaves[i] * value[i];
    }
    // printf("total is %lld\n", ret);
    return ret;
}

void init() {
    memset(value, 0, sizeof(value));
    memset(leaves, 0, sizeof(leaves));
    ans = 0;
    ini();
}

int main() {
    scanf("%d", &t);
    while (t--) {
        init();
        scanf("%d%lld", &n, &S);
        for (int i = 1; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
        }
        dfs();
        priority_queue<pii> que;
        for (int i = 2; i <= n; ++i) {
            que.push(
                make_pair(1ll * leaves[i] * (value[i] - value[i] / 2), i));
        }
        ll sum = total();
        while (sum > S) {
            int vert = que.top().second;
            // printf("value of vert(%d) is %d\n", vert, value[vert]);
            // printf("count of vert(%d) is %d\n", vert, leaves[vert]);
            que.pop();
            sum -= 1ll * leaves[vert] * (value[vert] - value[vert] / 2);
            value[vert] /= 2;
            que.push(make_pair(
                1ll * leaves[vert] * (value[vert] - value[vert] / 2), vert));
            // printf("pushed (%lld, %d) to que\n",
            // 1ll * leaves[vert] * value[vert], vert);
            ++ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 21 2020
