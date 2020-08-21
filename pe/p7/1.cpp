#include <cmath>
#include <cstdio>
using namespace std;
typedef long long ll;

bool check(ll x) {
    if (x == 1) {
        return false;
    }
    if (x == 2) {
        return true;
    }
    if (x & 1) {
        int top = sqrt(x) + 1;
        for (int i = 3; i <= top; ++i) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

int main() {
    int cnt = 0;
    int top = 2;
    while (cnt != 10001) {
        if (check(top)) {
            printf("%d is a prime\n", top);
            ++cnt;
        }
        ++top;
    }
    return 0;
}
