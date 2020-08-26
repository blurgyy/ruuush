#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int const rows = 15;
int const maxn = rows + 10;

int a[maxn][maxn];
int sum[maxn][maxn];

int main() {
    memset(sum, -1, sizeof(sum));
    memset(a, -1, sizeof(a));
    for (int i = 1; i <= rows; ++i) {
        for (int j = 1; j <= i; ++j) {
            scanf("%d", a[i] + j);
        }
    }
    sum[1][1] = a[1][1];
    for (int i = 2; i <= rows; ++i) {
        for (int j = 1; j <= i; ++j) {
            sum[i][j] = a[i][j] + max(sum[i - 1][j], sum[i - 1][j - 1]);
        }
    }
    int ans = -1;
    for (int i = 1; i <= rows; ++ i) {
        ans = max(ans, sum[rows][i]);
    }
    printf("ans is %d\n", ans);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 25 2020
