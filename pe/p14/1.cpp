#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long ll;
const int         maxn = 1000010;

int len[maxn];
template <typename T, size_t _size> struct STACK {
    T            a[_size];
    unsigned int sz;
    STACK() { init(); }
    void init() { sz = 0; }
    void push(T value) { a[sz++] = value; }
    void pop() { --sz; }
    T    top() { return a[sz]; }
    int  size() { return sz; }
};

int calc(int n) {
    ll x = n;
    while (x != 1) {
        if (x < maxn && len[x] != 0) {
            break;
        }
        if (x & 1) {
            x = 3 * x + 1;
        } else {
            x /= 2;
        }
        ++len[n];
    }
    if (n != x) {
        len[n] += len[x];
    }
    return len[n];
}

void init() {
    memset(len, 0, sizeof(len));
    len[1] = 1;
}

int main() {
    init();
    // int x;
    // while (~scanf("%d", &x)) {
    // printf("chain length of %d is %d\n", x, calc(x));
    // }
    int maxchain = -1;
    int ans      = -1;
    for (int i = 2; i < maxn; ++i) {
        // maxchain = std::max(maxchain, calc(i));
        int curchain = calc(i);
        // printf("chain length of %d is %d\n", i, curchain);
        if (maxchain < curchain) {
            maxchain = curchain;
            ans      = i;
        }
    }
    printf("%d\n", ans);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 22 2020
