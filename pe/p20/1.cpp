#include <cstdio>
#include <vector>
using namespace std;

void output(vector<int> v, bool lf = true) {
    for (int i = v.size() - 1; i >= 0; --i) {
        printf("%d%c", v[i], i == 0 ? lf ? '\n' : '\0' : '\0');
    }
}

vector<int> store(int x) {
    vector<int> ret;
    if (x == 0) {
        ret.push_back(0);
    } else {
        while (x) {
            ret.push_back(x % 10);
            x /= 10;
        }
    }
    return ret;
}

vector<int> mul(vector<int> const &lhs, vector<int> const &rhs) {
    int         lenl = lhs.size();
    int         lenr = rhs.size();
    int         top  = lenl + lenr;
    vector<int> ret(top, 0);
    // Initialization
    for (int i = 0; i < lhs.size(); ++i) {
        for (int j = 0; j < rhs.size(); ++j) {
            ret[i + j] += lhs[i] * rhs[j];
        }
    }
    for (int i = 0; i < top; ++i) {
        if (ret[i] > 9) {
            ret[i + 1] += ret[i] / 10;
            ret[i] %= 10;
        }
    }
    while (top > 1 && ret[top - 1] == 0) {
        --top;
    }
    ret.erase(ret.begin() + top, ret.end());
    return ret;
}

// top must be greater than 0
vector<int> pow(int const bot, int const top) {
    // printf("Called pow with (bot = %d, top = %d)\n", bot, top);
    vector<int> ret;
    vector<int> base = store(bot);
    if (top == 0) {
        ret = store(0);
    } else if (top == 1) {
        ret = base;
    } else {
        int mid = top / 2;
        ret = mul(pow(bot, mid), pow(bot, top - mid));
    }
    return ret;
}

vector<int> fact(int const value) {
    vector<int> ret = store(1);
    if (value <= 1) {
        return ret;
    }
    for (int i = 1; i <= value; ++ i) {
        ret = mul(ret, store(i));
    }
    return ret;
}

void testmul() {
    int x, y;
    while (~scanf("%d%d", &x, &y)) {
        vector<int> lhs = store(x);
        vector<int> rhs = store(y);
        vector<int> ans = mul(lhs, rhs);
        output(ans);
    }
}

void testpow() {
    int x, y;
    while (~scanf("%d%d", &x, &y)) {
        // vector<int> bot = store(x);
        // vector<int> top = store(y);
        vector<int> ans = pow(x, y);
        output(ans);
    }
}

void solve() {
    int x;
    while (~scanf("%d", &x)) {
        vector<int> ans = fact(x);
        // output(ans);
        int sum = 0;
        for (int i = 0; i < ans.size(); ++ i) {
            sum += ans[i];
        }
        printf("sum is %d\n", sum);
    }
}

int main() {
    // testmul();
    // testpow();
    solve();
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Aug 26 2020
