#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

#define maxn 100010
typedef unsigned long long ull;
struct StringHasher{
    ull seed;
    int len;
    char s[maxn];
    ull h[26][maxn], _[maxn];
    StringHasher(ull _seed = 998244353):
        seed(_seed){
        _[0] = 1;
        if(!_[1]){
            for(int i = 1; i < maxn; ++ i){
                _[i] = _[i-1] * seed;
            }
        }
    }

    ull getHash(int l, int r, int shift = 0){  ///gets substring[l, r]'s Hash value in O(1)
        return h[shift][l] - h[shift][r+1] * _[r-l+1];
    }
    bool check(int x, int y, int length, int diff = 0){   ///substring[x, x+len-1] == substring[y, y+len-1] ? true : false
        ull h1 = getHash(x, x + length - 1, diff);
        ull h2 = getHash(y, y + length - 1);
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
    char trans(char ch, int shift){
        if((int)ch + shift > 'z')ch -= 26;
        return ch + shift;
    }
    void init(char *s){
        len = strlen(s);
        for(int j = 0; j < 26; ++ j){
            h[j][len] = 0;
        }
        for(int j = 0; j < 26; ++ j){
            for(int i = len-1; i >= 0; -- i){
                h[j][i] = h[j][i+1] * seed + trans(s[i], j);
            }
        }
    }
}hasher(1e9+7);
#undef maxn
int len, q, x, y;
char s[maxn];

int main(){
    while(~scanf("%d%s%d", &len, s, &q)){
        hasher.init(s);
        while(q --){
            scanf("%d%d%d", &x, &y, &len);
            x --;
            y --;
            if(s[y] < s[x]) swap(x, y);
            int diff = s[y] - s[x];
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