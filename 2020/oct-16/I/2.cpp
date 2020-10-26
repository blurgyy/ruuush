#include <bits/stdc++.h>
using namespace std;

int const    maxn = 50010;
double const eps  = 1e-8;

int  T, n;
bool invalid[maxn];
struct LINE {
    int  a, b;
    bool operator<(LINE const &rhs) {
        if (b == rhs.b) {
            return a > rhs.a;
        } else {
            return b > rhs.b;
        }
    }
} line[maxn];
struct STACK {
    int a[maxn];
    int sz;
    STACK() { init(); }
    void init() { sz = 0; }
    int  size() const { return sz; }
    void push(int x) { a[sz++] = x; }
    void pop() { --sz; }
    int  top() { return a[sz - 1]; }
    int  subtop() {
        assert(sz >= 2);
        return a[sz - 2];
    }
} stk, incre;

double isect(LINE const &l1, LINE const &l2) {
    int a1 = l1.a, b1 = l1.b;
    int a2 = l2.a, b2 = l2.b;
    if (a1 == a2) {
        return 0;
    }
    return 1.0 * (b2 - b1) / (a1 - a2);
}

void init() {
    memset(invalid, false, sizeof(invalid));
    incre.init();
    stk.init();
}

int main() {
    scanf("%d", &T);
    while (T--) {
        init();

        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &line[i].b, &line[i].a);
        }
        sort(line, line + n);
        // for (int i = 0; i < n; ++ i) {
        // printf("%d %d\n", line[i].b, line[i].a);
        // }
        // return 0;

        int maxa = -1;
        for (int i = 0; i < n; ++i) {
            if (i && line[i].a == line[i - 1].a &&
                line[i].b == line[i - 1].b) {
                invalid[i - 1] = invalid[i] = true;
            }
            if (line[i].a > maxa) {
                incre.push(i);
                maxa = line[i].a;
            }
        }

        for (int i = 0; i < incre.size(); ++i) {
            while (stk.size() >= 2) {
                LINE now    = line[incre.a[i]];
                LINE top    = line[stk.top()];
                LINE subtop = line[stk.subtop()];
                if (isect(now, top) <= isect(top, subtop)) {
                    stk.pop();
                } else {
                    break;
                }
            }
            stk.push(incre.a[i]);
        }

        int ans = 0;
        for (int i = 0; i < stk.size(); ++i) {
            if (!invalid[stk.a[i]]) {
                ++ans;
                // LINE x = line[stk.a[i]];
                // printf("a=%d, b=%d\n", x.a, x.b);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Oct 17 2020
