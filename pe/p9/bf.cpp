#include <cmath>
#include <cstdio>
const double eps = 1e-7;

int main() {
    for (int c = 5; c < 1000; ++c) {
        for (int a = 3; a < c; ++a) {
            double double_b = sqrt(c * c - a * a);
            int    b        = (int)(double_b + eps);
            if (fabs(double_b - (double)b) > eps) {
                continue;
            }
            if (a + b + c == 1000) {
                printf("%d^2 + %d^2 = %d^2\n", a, b, c);
                printf("prod is %d\n", a * b * c);
            }
        }
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 21 2020
