#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[20], rot[20];

long long prime[6] = {2, 3, 5, 233, 331};
long long qmul(long long x, long long y, long long mod) { // ³Ë·¨·ÀÖ¹Òç³ö£¬ Èç¹ûp * p²»±¬LLµÄ»°¿ÉÒÔÖ±½Ó³Ë£» O(1)³Ë·¨»òÕß×ª»¯³É¶þ½øÖÆ¼Ó·¨


    return (x * y - (long long)(x / (long double)mod * y + 1e-3) *mod + mod) % mod;
    /*
    long long ret = 0;
    while(y) {
        if(y & 1)
            ret = (ret + x) % mod;
        x = x * 2 % mod;
        y >>= 1;
    }
    return ret;
    */
}
long long qpow(long long a, long long n, long long mod) {
    long long ret = 1;
    while(n) {
        if(n & 1) ret = qmul(ret, a, mod);
        a = qmul(a, a, mod);
        n >>= 1;
    }
    return ret;
}

bool Miller_Rabin(long long p) {
    if(p < 2) return 0;
    if(p != 2 && p % 2 == 0) return 0;
    long long s = p - 1;
    while(!(s & 1)) s >>= 1;
    for(int i = 0; i < 5; ++ i) {
        if(p == prime[i]) return 1;
        long long t = s, m = qpow(prime[i], s, p);
        while(t != p - 1 && m != 1 && m != p - 1) {
            m = qmul(m, m, p);
            t <<= 1;
        }
        if(m != p - 1 && !(t & 1)) return 0;
    }
    return 1;
}

int transform(char ch){
    if(ch == '6')return 9;
    if(ch == '9')return 6;
    return ch - '0';
}

int main(){
/*
    for(int i = 0; i < 10; ++ i){
        printf("%d: %d\n", i, transform('0' + i));
    }
*/
    while(~scanf("%s", s)){
        int len = strlen(s);
        long long n = 0;
        bool ans = true;
        for(int i = 0; i < len; ++ i){
            n *= 10;
            int pos = len - i - 1;
            if(s[pos] == '3' || s[pos] == '7' || s[pos] == '4'){
                ans = false;
                break;
            }
            n += transform(s[pos]);
        }
        //printf("n = %lld\n", n);
        if(ans)ans = Miller_Rabin(n);
        printf("%s\n", ans ? "yes" : "no");
    }
    return 0;
}