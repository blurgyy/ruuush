#include <cassert>
#include <cstdio>
#include <cstring>
const int maxn = 2000010;

int isprime[maxn];

void init() {
    // -1 stands for "undefined"
    // 0/false stands for "not a prime"
    // 1/true stands for "is a prime"
    memset(isprime, -1, sizeof(isprime));
    isprime[2] = true;
    int base   = 2;
    while (base < maxn) {
        for (int iter = base + base; iter < maxn; iter += base) {
            isprime[iter] = false;
        }
        while (base < maxn && isprime[base] != -1) {
            ++base;
        }
        isprime[base] = true;
    }
}

int main() {
    init();
    long long ans = 0;
    for (int i = 2; i < 2000000; ++i) {
        if (isprime[i] == 1) {
            ans += i;
        }
    }
    printf("ans = %lld\n", ans);
    return 0;
}
