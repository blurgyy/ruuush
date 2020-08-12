#include <bits/stdc++.h>
using namespace std;
const int maxn = 60;

int T, n;
int w[maxn];
int ans;

int count(int i, int j) {
    int ret = 0;
    int s   = w[i] + w[j];
    int x = 0, y = n-1;
    while(x < y) {
        int cur = w[x] + w[y];
        if(cur < s) {
            ++ x;
        } else if (cur == s) {
            ++ ret;
            ++ x, -- y;
        } else {
            -- y;
        }
    }
    return ret;
}

void init() { ans = 0; }

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        init();
        for (int i = 0; i < n; ++i) {
            scanf("%d", w + i);
        }
        sort(w, w + n);
        for (int i = 0; i < n; ++i) {
            for (int j = n - 1; j > i; --j) {
                int cur_ans = count(i, j);
                if (ans < cur_ans) {
                    ans = cur_ans;
                }
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}

// Author: Blurgy
// Date:   Aug 11 2020
