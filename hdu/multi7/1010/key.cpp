///what is this..
///

#include <cstdio>

const int N = 200000;

int a[N];

int main()
{
    int T;
    scanf("%d", &T);
    while (T --) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            scanf("%d", a + i);
        }
        for (int k = 0; 1 << k <= m; ++ k) {
            if (m >> k & 1) {
                for (int i = 1 << k; i < n; ++ i) {
                    a[i] ^= a[i - (1 << k)];
                }
            }
        }
        for (int i = 0; i < n; ++ i) {
            printf("%d%c", a[i], " \n"[i == n - 1]);
        }
    }
}
