//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 500010;

#define maxn 500010
typedef unsigned long long ull;
struct StringHasher{
    ull seed;
    int len;
    char s[maxn];
    ull h[maxn], _[maxn];
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
        return h[l] - h[r+1] * _[r-l+1];
    }
    bool check(int x, int y, int length){   ///substring[x, x+len-1] == substring[y, y+len-1] ? true : false
        ull h1 = getHash(x, x + length - 1);
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
    void init(char *s){
        len = strlen(s);
        h[len] = 0;
        for(int i = len-1; i >= 0; -- i){
            h[i] = h[i+1] * seed + s[i];
        }
    }
}hasher(1e9+7), hasher_(1e9+9), hasher__;
#undef maxn
int T, n;
int len[maxn];
char s[maxn];
char *stp[maxn];

void in(){
    int cur = 1;
    stp[0] = s;
    for(int i = 1; i <= n; ++ i){
        stp[i] = s + cur;
        scanf("%s", stp[i]);
        len[i] = strlen(stp[i]);
        cur += len[i] + 1;
    }
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        in();
        char *suf = NULL;
        for(int i = n; i >= 1; -- i){
            char *now = stp[i];
            //printf("now = %s\n", now);
            //char tmpch = *(now+len[i]);
            //*(now+len[i]) = 0;
            hasher.init(now);
            hasher_.init(now);
            hasher__.init(now);
            //*(now+len[i]) = tmpch;

            int pos = len[i] - 1;
            for(int j = 0; j < len[i]; ++ j){
                int lcp = hasher.lcp(j, pos);
                int lcp_ = hasher_.lcp(j, pos);
                if(lcp != lcp_){
                    lcp = hasher__.lcp(j, pos);
                }
                //printf("j = %d, pos = %d, lcp = %d\n", j, pos, lcp);
                if(now[j+lcp] < now[pos+lcp]){
                    pos = j;
                }
            }

            now += pos;
            //printf("suf = %s\n", now);
            char *nxt = stp[i-1] + len[i-1];
            while(true){
                *nxt = *now;
                if(*now == 0){
                    break;
                }
                ++ nxt;
                ++ now;
            }
        }
        printf("%s\n", stp[0]);
    }
    return 0;
}