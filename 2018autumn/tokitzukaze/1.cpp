#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

char s[maxn];
typedef unsigned long long ull;
template<size_t maxn>
struct StringHasher{
    ull seed;
    int len;
    ull h[25][maxn], _[maxn];
    StringHasher(ull _seed = 998244353):
        seed(_seed){
        _[0] = 1;
        for(int i = 1; i < maxn; ++ i){
            _[i] = _[i-1] * seed;
        }
    }

    char trans(char ch, int sh){
        if((int)ch + sh > 'z')ch = ch - 26 + sh;
        else ch += sh;
        return ch;
    }
    ull getHash(int l, int r, int sh = 0){  ///gets substring[l, r]'s Hash value in O(1)
        printf("_[%d] = %llu\n", r-l+1, _[r-l+1]);
        printf("%llu - %llu * %llu = %llu\n", h[sh][l], h[sh][r+1], _[r-l+1], h[sh][l] - h[sh][r+1] * _[r-l+1]);
        return h[sh][l] - h[sh][r+1] * _[r-l+1];
    }
    bool check(int x, int y, int length){   ///substring[x, x+len-1] == substring[y, y+len-1] ? true : false
        ull h1 = getHash(x, x + length - 1);
        ull h2 = getHash(y, y + length - 1);
        return h1 == h2;
    }
    bool check(int x, int y, int length, int diff){
        ull h1 = getHash(x, x + length - 1, diff);
        ull h2 = getHash(y, y + length - 1);
        printf("h1(%d, %d, %d) = %llu, h2(%d, %d, %d) = %llu\n", x, x + length - 1, diff, h1, y, y + length - 1, 0, h2);
        return h1 == h2;
    }
    int bs(int x, int y, int left, int right){
        if(left >= right)return right;
        int mid = (left + right + 1) / 2;       ///upper_bound
        if(check(x, y, mid))return bs(x, y, mid, right);
        return bs(x, y, left, mid - 1);
    }
    int lcp(int x, int y){      ///returns length of the longest common prefix of suffix[x] and suffix[y]
        int minl = 0;
        int maxl = max(0, min(len - x + 1, len - y + 1));
        return bs(x, y, minl, maxl);
    }
    void init(char *s){
        len = strlen(s);
        // h[len] = 0;
        for(int i = 0; i < 26; ++ i){
            h[i][len] = 0;
        }
        for(int j = 0; j < 26; ++ j){
            for(int i = len-1; i >= 0; -- i){
                h[j][i] = h[j][i+1] * seed + trans(s[i], j);
                printf("h[%d][%d] = %llu\n", j, i, h[j][i]);
            }
            printf("\n");
        }

        _[0] = 1;
        for(int i = 1; i < maxn; ++ i){
            _[i] = _[i-1] * seed;
        }
    }
};
StringHasher<maxn> hasher(1e9+7), hasher_(1e9+9), hasher__;
int asdf, q;

int main(){
    // char t[10] = "abcdefg";
    // hasher.init(t);
    // printf("%llu %llu\n", hasher.getHash(0, 2), hasher.getHash(1, 3) - hasher.shift[2]);

    while(~scanf("%d%s%d", &asdf, s, &q)){
        hasher.init(s);
        int x, y, len;
        while(q --){
            scanf("%d%d%d", &x, &y, &len);
            if(s[y] < s[x]) swap(x, y);
            int diff = s[y] - s[x];
            printf("diff = %d\n", diff);
            if(hasher.check(x, y, len, diff)){
                printf("%d\n", min(diff, 26 - diff));
            }
            else {
                printf("-1\n");
            }
        }
    }
    return 0;
}

/**

2 ab 100
0 1 1

10 
aabbcdedcz
40
0 2 2
1 5 2
3 5 4
0 9 1

*/