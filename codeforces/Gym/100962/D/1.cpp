#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n, q, l, r;
char s[maxn];

#define maxn 200010
typedef unsigned long long ull;
struct StringHasher{
    ull seed;
    int len;
    char s[maxn];
    ull h[2][maxn], _[maxn];
    StringHasher(ull _seed = 998244353):
        seed(_seed){
        _[0] = 1;
        if(!_[1]){
            for(int i = 1; i < maxn; ++ i){
                _[i] = _[i-1] * seed;
            }
        }
    }

    ull getHash(int l, int r){  ///gets substring[l, r]'s Hash value in O(1)
        printf("%llu - %llu * %llu = %llu\n", h[0][l], h[0][r+1], _[r-l+1], h[0][l] - h[0][r+1] * _[r-l+1]);
        return h[0][l] - h[0][r+1] * _[r-l+1];
    }
    ull getHash__(int l, int r){  ///gets substring[l, r]'s Hash value in O(1)
        printf("%llu - %llu * %llu = %llu\n", h[1][r+1], h[1][l], _[r-l+1], h[1][r+1] - h[1][l] * _[r-l+1]);
        return h[1][r+1] - h[1][l] * _[r-l+1];
    }
    bool check(int x, int y, int length){   ///substring[x, x+len-1] == substring[y, y+len-1] ? true : false
        ull h1 = getHash(x, x + length - 1);
        ull h2 = getHash__(y, y - length + 1);
        printf("(%d, %d), (%d, %d) = %s\n", x, x+length-1, y-length+1, y, h1==h2?"same":"diff");
        return h1 == h2;
    }
    int bs(int x, int y, int left, int right){
        if(left >= right)return right;
        int mid = (left + right + 1) / 2;       ///upper_bound
        if(check(x, y, mid))return bs(x, y, mid, right);
        return bs(x, y, left, mid - 1);
    }
    int solve(int x, int y){      ///returns length of the longest common prefix of suffix[x] and suffix[y]
        int minl = 0;
        int maxl = y - x + 1;
        return bs(x, y, minl, maxl);
    }
    void init(char *s){
        len = strlen(s);
        h[0][len] = h[1][0] = 0;
        for(int i = len-1; i >= 0; -- i){
            h[0][i] = h[0][i+1] * seed + s[i];
            //printf("h[0][%d] = %llu\n", i, h[0][i]);
        }
        for(int i = 1; i <= len; ++ i){
            h[1][i] = h[1][i-1] * seed + s[i-1];
            //printf("h[1][%d] = %llu\n", i, h[1][i]);
        }
    }
}hasher(1e9+7), hasher_(1e9+9), hasher__;
#undef maxn

int main(){
    while(~scanf("%d%d%s", &n, &q, s)){
        hasher.init(s);
        // while(true){
        //     scanf("%d%d", &l, &r);
        //     printf("h = (%llu, %llu)\n", hasher.getHash(l,r), hasher.getHash__(l,r));
        // }
        while(q --){
            scanf("%d%d", &l, &r);
            l --, r --;
            printf("h = (%llu, %llu)\n", hasher.getHash(l,r), hasher.getHash__(l,r));
            printf("%d\n", hasher.solve(l, r));
        }
    }
    return 0;
}

/**

11 3
gabacababad
2 8
1 3
6 10

*/