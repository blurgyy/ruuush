#include <bits/stdc++.h>
using namespace std;
// int const    maxn = 50010;
int const    maxn = 100010;
double const eps  = 1e-8;

int T, n;
struct LINE {
    int  a, b;
    int  dup;
    bool operator<(LINE const &rhs) {
        if (a == rhs.a) {
            return b > rhs.b;
        } else {
            return a < rhs.a;
        }
    }
    bool operator==(LINE const &rhs) { return a == rhs.a && b == rhs.b; }
} line[maxn];
struct STACK {
    int a[maxn];
    int sz;
    STACK() { init(); }
    void init() { sz = 0; }
    void push(int x) {
        // printf("pushing %d\n", x);
        a[sz++] = x;
    }
    void pop() {
        // printf("popped %d\n", top());
        --sz;
    }
    int top() { return a[sz - 1]; }
    int subtop() {
        // assert(sz >= 2);
        return a[sz - 2];
    }
    void out() {
        for (int i = 0; i < sz; ++i) {
            printf("%d%c", a[i], " \n"[i + 1 == sz]);
        }
    }
} stk;

double intersect(LINE const &l1, LINE const &l2) {
    int a1 = l1.a, b1 = l1.b;
    int a2 = l2.a, b2 = l2.b;
    // assert(a1 != a2);
    if (1ll * (b2 - b1) * (a1 - a2) >= 0) {
        return 2.0 * (b1 - b2) / (a2 - a1);
    }
    return -1;
}

void init() {
    memset(line, 0, sizeof(line));
    stk.init();
}

int main() {
    // freopen("in4.in", "r", stdin);
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &line[i].b, &line[i].a);
        }
        // printf("read finished\n");
        sort(line, line + n);
        for (int i = 0, nxt = 1; i < n; i = nxt) {
            nxt = i + 1;
            for (nxt = i + 1; nxt < n; ++nxt) {
                if (!(line[i] == line[nxt])) {
                    break;
                }
                line[nxt].dup = -1;
            }
            line[i].dup = nxt - i;

            while (line[nxt].a == line[i].a) {
                line[nxt].dup = -1;
                ++nxt;
            }
        }
        // printf("preprocess finished\n");
        for (int i = 0; i < n; ++i) {
            LINE now = line[i];
            if (now.dup <= 0) {
                continue;
            }
            // stack size == 0
            if (stk.sz == 0) {
                stk.push(i);
                continue;
            }

            // stack size == 1
            LINE   top   = line[stk.top()];
            double isect = intersect(now, top);
            if (stk.sz == 1) {
                if (isect <= eps) {
                    stk.pop();
                }
                stk.push(i);
                continue;
            }

            // stack size >= 2

            LINE   subtop   = line[stk.subtop()];
            double subisect = intersect(top, subtop);
            // assert(subisect > eps); // subisect always exists

            // while (isect < subisect) {
            while (isect < subisect || fabs(isect - subisect) < eps) { // <=
                stk.pop();

                if (stk.sz < 2) {
                    break;
                }

                top    = subtop;
                subtop = line[stk.subtop()];

                isect    = intersect(now, top);
                subisect = intersect(top, subtop);
            }
            stk.push(i);
        }
        int ans = 0;
        for (int i = 0; i < stk.sz; ++i) {
            if (line[stk.a[i]].dup != 1) {
                continue;
            }
            ans += line[stk.a[i]].dup;
        }
        printf("%d\n", ans);
        // printf("%d\n", stk.sz + dup);
        // stk.out();
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Oct 17 2020
