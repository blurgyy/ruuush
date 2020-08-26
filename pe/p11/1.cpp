#include <algorithm>
#include <cassert>
#include <cstdio>
typedef long long ll;
const size_t      size = 20;
const size_t      maxn = size + 10;
// So there are in fact 4 directions, including the anti-diagonal direction.
const int dx[] = {1, 1, 0, -1};
const int dy[] = {0, 1, 1, 1};

int a[maxn][maxn];

bool inrange(int x, int y) {
    bool ret = (x >= 0 && y >= 0 && x < size && y < size);
    printf("point (%d, %d) %s\n", x, y, ret ? "in range" : "out of range");
    return ret;
}

int main() {
    freopen("in.in", "r", stdin);
    ll ans = -1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // scanf("%d", a[i] + j);
            scanf("%d", a[j] + i);
        }
    }
    // for (int i = 0; i < size; ++ i) {
    // for (int j = 0; j < size; ++ j) {
    // printf("%02d ", a[i][j]);
    // }
    // printf("\n");
    // }
    // return 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int d = 0; d < 4; ++d) {
                if (inrange(i + 3 * dx[d], j + 3 * dy[d])) {
                    ll prod = 1;
                    for (int k = 0; k < 4; ++k) {
                        int ni = i + k * dx[d];
                        int nj = j + k * dy[d];
                        prod *= 1ll * a[ni][nj];
                        // printf("a[%02d][%02d] ", ni, nj);
                    }
                    // printf("\n");
                    ans = std::max(ans, prod);
                    // printf("intermediate = %08d\n", prod);
                }
            }
        }
    }
    printf("%lld\n", ans);
    fclose(stdin);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 22 2020
