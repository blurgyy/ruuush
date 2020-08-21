#include <cstdio>
#include <cmath>
#include <algorithm>

// 999 * 999 = 998001;

bool check(int x, int y) {
    int prod = x * y;
    int nprod = 0;
    while (prod) {
        int digit = prod % 10;
        nprod = nprod * 10 + digit;
        prod /= 10;
    }
    return nprod == x * y;
}

int main() {
    int ans = 0;
    for (int i = 999; i > 99; -- i) {
        for (int j = 999; j > 99; -- j) {
            if (check(i, j)) {
                ans = std::max(ans, i * j);
            }
        }
    }
    printf("ans = %d\n", ans);
    return 0;
}
