#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int         T, n;
char        s[maxn];
vector<int> rec[2];
int         ans, bel[maxn], avail[2];

int bs(int arr[], int e, int left, int right) {
    int mid = (left + right) / 2;
    return left >= right ? right
                         : e <= arr[mid] ? bs(arr, e, left, mid)
                                         : bs(arr, e, mid + 1, right);
}

void init() {
    ans = 0;
    rec[0].clear(), rec[1].clear();
    memset(bel, -1, sizeof(bel));
    memset(avail, 0, sizeof(avail));
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, s);
        init();
        for (int i = 0; i < n; ++i) {
            int ch = s[i] - '0';
            int op = 1 - ch;
            rec[ch].push_back(i);
            int chsize = rec[ch].size();
            int opsize = rec[op].size();
            // if (opsize == 0 || rec[op][opsize-1]
            if (avail[op] == rec[op].size()) {
                bel[i] = ++ans;
            } else {
                bel[i] = bel[rec[op][avail[op]++]];
            }
        }
        printf("%d\n", ans);
        for (int i = 0; i < n; ++i) {
            printf("%d%c", bel[i], i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

// Author: Blurgy
// Date:   Aug 12 2020
