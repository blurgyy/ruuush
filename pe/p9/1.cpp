// This construction method does not solve problem 9.  See ./bf.cpp instead.
#include <cassert>
#include <cstdio>

// Construct Pythagorean triplets:
// a = 2*x*x + 2*x
// b = 2*x+1
// c = a+1
// satisfies:
//  c*c = a*a + b*b

int main() {
    for (int i = 1;; ++i) {
        int a = 2 * i * i + 2 * i;
        int b = 2 * i + 1;
        int c = a + 1;
        if (a > 1000) {
            break;
        }
        assert(a * a + b * b == c * c);
        // if (a + b + c == 1000) {
        printf("%d %d %d ", a, b, c);
        printf("prod is %d\n", a * b * c);
        // }
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 21 2020
