#include <cassert>
#include <cstdio>
#include <cstring>
const int maxn = 10010;

int lhs[maxn];
int rhs[maxn];
int ans[maxn];
int a[maxn], b[maxn];

void output(int *arr, int len) {
    for (int i = len - 1; i >= 0; --i) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

// Multiplication for large integers
//
// Multiplies lhs with rhs, store the result in the __global__ array ret,
// returns total number of digits in ret.
// All values (lhs, rhs, and ret) are stored in reversed order, aka the number
// 123 will be stored in array *a as a[0] = 3, a[1] = 2, a[2] = 1
int mul(int *lhs, int lenl, int *rhs, int lenr, int *retarr) {
    // printf("called mul(*, lenl=%d, *, lenr=%d, *)\n", lenl, lenr);
    // output(lhs, lenl);
    // output(rhs, lenr);
    // assert(lhs != rhs);
    // assert(lhs != retarr);
    // assert(rhs != retarr);
    // Initialization
    int top = lenl + lenr;
    for (int i = 0; i < top; ++i) {
        retarr[i] = 0;
    }

    // Multiplication
    for (int j = 0; j < lenr; ++j) {
        for (int i = 0; i < lenl; ++i) {
            retarr[i + j] += lhs[i] * rhs[j];
        }
    }

    // Finalization
    int ret;
    for (ret = 0; ret < top; ++ret) {
        if (retarr[ret] >= 10) {
            retarr[ret + 1] += retarr[ret] / 10;
            retarr[ret] %= 10;
        }
    }
    while (ret > 1 && retarr[ret - 1] == 0) {
        --ret;
    }
    // assert(ret > 0);
    // printf("mul returns ");
    // output(retarr, ret);
    return ret;
}

int store(int x, int *arr) {
    if (x == 0) {
        arr[0] = 0;
        return 1;
    }
    int len = 0;
    while (x) {
        arr[len++] = x % 10;
        x /= 10;
    }
    return len;
}

int store(int *from, int *to, int len) {
    for (int i = 0; i < len; ++i) {
        to[i] = from[i];
    }
    return len;
}

int pow(int bot, int top, int *arr) {
    // printf("called pow(%d, %d, *)\n", bot, top);
    if (top == 0) {
        return store(1, arr);
    } else if (top == 1) {
        return store(bot, arr);
    }
    int left  = top / 2;
    int right = top - left;
    int ret   = mul(lhs, pow(bot, left, lhs), rhs, pow(bot, right, rhs), arr);
    // printf("pow(%d, %d, *) returns ", bot, top);
    // output(arr, ret);
    return ret;
}

int testmul() {
    int x, y;
    while (~scanf("%d%d", &x, &y)) {
        int lenl   = store(x, lhs);
        int lenr   = store(y, rhs);
        int lenans = mul(lhs, lenl, rhs, lenr, ans);
        for (int i = lenans - 1; i >= 0; --i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
        printf("actual ans is: %d\n", x * y);
    }
    return 0;
}

int testpow() {
    int x, y;
    while (~scanf("%d%d", &x, &y)) {
        int len = pow(x, y, ans);

        for (int i = 0; i < 5; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");

        printf("length of %d^%d: %d\n", x, y, len);
        for (int i = len - 1; i >= 0; --i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}

int main() {
    // freopen("in", "r", stdin);
    // return testmul();
    // return testpow();
    int lenl = 2;
    int lenr = 2;
    store(2, lhs);
    store(1, rhs);
    printf("begins\n");
    for (int i = 0; i < 10000; ++i) {
        // printf("i = %d\n", i);
        lenr = mul(lhs, lenl, rhs, lenr, ans);
        store(ans, rhs, lenr);
        // output(ans, lenr);
    }
    printf("ends\n");
    // output(ans, lenr);
    int sum = 0;
    for (int i = 0; i < lenr; ++i) {
        sum += ans[i];
    }
    printf("sum is %d\n", sum);
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 23 2020
