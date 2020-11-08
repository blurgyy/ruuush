#include <bits/stdc++.h>
using namespace std;
size_t const maxn = 151;

char const *ans =
    "###..########.#################.#..#..#..##.##..#....##.##.##.#"
    "..################..########.#..##....#..#..##.#..##.#..####..#"
    "######..#######..#######";
char str[maxn];

void output(int val, int ind) {
    int base = ind * 30;
    printf("%c%c%c", ans[val * 3 + base + 0], ans[val * 3 + base + 1],
           ans[val * 3 + base + 2]);
}

int main() {
    // printf("%d\n", strlen(ans));
    while (~scanf("%s", str)) {
        int len = strlen(str);
        for (int ind = 0; ind < 5; ++ind) {
            for (int i = 0; i < len; ++i) {
                int val = str[i] - '0';
                output(val, ind);
                printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Nov 08 2020, 12:59 [CST]
