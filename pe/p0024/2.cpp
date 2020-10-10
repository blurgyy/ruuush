#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int         maxn = 21;

int n;
ll  th;
ll  frac[maxn];

void init() {
    frac[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        frac[i] = 1ll * frac[i - 1] * i;
        // printf("frac[%d] = %lld\n", i, frac[i]);
    }
}

vector<int> genseq(int const &n) {
    vector<int> ret;
    for (int i = 0; i < n; ++i) {
        ret.push_back(i);
    }
    return ret;
}

// @brief:
//      This is the recursive version implementation of the upper_bound
//      function.
int bs(int left, int right, ll arr[], ll e) {
    if (left >= right) {
        return right;
    }
    // // lower_bound implementation:
    // int mid = (left + right) / 2;
    // if (e <= arr[mid]) {
    // return bs(left, mid, arr, e);
    // } else {
    // return bs(mid + 1, right, arr, e);
    // }

    // upper_bound implementation
    int mid = (left + right + 1) / 2; // upper_bound
    if (e < arr[mid]) {
        return bs(left, mid - 1, arr, e);
    } else {
        return bs(mid, right, arr, e);
    }
}

// @param seq:
//      The sequence to be permutated, elements should be in ascending order
// @param th:
//      The index of the desired permutation.
// @return:
//      The desired permutation.
vector<int> solve(vector<int> const &seq, ll const &th) {
    vector<int> ret;

    int len = seq.size();

    if (len == 0) {
        return ret;
    }

    int pos = bs(0, maxn - 1, frac, th - 1);
    // printf("frac[%d] < %lld <= frac[%d]\n", pos, th, pos + 1);

    int div     = th / frac[pos];
    int mod     = th % frac[pos];
    int baseend = len - (pos + 1);
    for (int i = 0; i < baseend; ++i) {
        ret.push_back(seq[i]);
    }
    if (mod == 0) {
        div -= 1;
        mod = frac[pos];
    }
    ret.push_back(seq[baseend + div]);
    ++baseend;

    vector<int> rest;
    for (int i = 0; i < len; ++i) {
        if (find(ret.begin(), ret.end(), seq[i]) == ret.end()) {
            rest.push_back(seq[i]);
        }
    }
    int nxtth = mod;

    rest = solve(rest, nxtth);
    for (auto elem : rest) {
        ret.push_back(elem);
    }

    assert(ret.size() == len);
    return ret;
}

int main() {
    init();
    freopen("in.in", "r", stdin);
    while (~scanf("%d%lld", &n, &th)) {
        vector<int> ans = solve(genseq(n), th);
        for (auto x : ans) {
            printf("%d", x);
        }
        printf("\n");
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Oct 10 2020
