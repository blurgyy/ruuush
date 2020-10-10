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
        printf("frac[%d] = %lld\n", i, frac[i]);
    }
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

// @param start:
//      The least element in the sequence to be permutated.
// @param end:
//      The greatest element in the sequence to be permutated.
// @param th:
//      The index of the desired permutation.
// @return:
//      The desired permutation.
vector<int> solve(int const &start, int const &end, ll const &th) {
    printf("starting function solve() with start = %d, end = %d\n", start,
           end);
    assert(start <= end);
    vector<int> ret;

    int len = end - start + 1;
    int pos = bs(0, maxn - 1, frac, th - 1);
    printf("frac[%d] < %lld <= frac[%d]\n", pos, th, pos + 1);

    int div = th / frac[pos];
    int mod = th % frac[pos];

    int baseend = end - (pos + 1) + (mod > 0);
    printf("baseend is %d\n", baseend);
    for (int i = start; i <= baseend; ++i) {
        ret.push_back(i);
    }

    int nxtth = mod;
    if (nxtth == 0) {
        for (int i = end; i > baseend; --i) {
            ret.push_back(i);
        }
        assert(ret.size() == len);
        return ret;
    }

    vector<int> rest = solve(baseend + 1, end, nxtth);
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
        vector<int> ans = solve(0, n, th);
        for (auto x : ans) {
            printf("%d\n", x);
        }
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Oct 10 2020
