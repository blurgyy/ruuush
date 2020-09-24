#include <cmath>
#include <cstdio>
typedef long long ll;
const ll          problem = 600851475143;
// 600,851,475,143

int main() {
    // printf("%f\n", sqrt(problem));
    ll n    = problem;
    ll fact = 3;
    ll maxx = fact;
    while (n > 1) {
        while (n % fact == 0) {
            n /= fact;
            maxx = fact;
        }
        ++fact;
    }
    printf("maxx = %lld\n", maxx);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 21 2020
