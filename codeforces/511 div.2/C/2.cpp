#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 300010;

int n;
int a[maxn];
map<int, int> rec;  ///<prime, cnt>

LL prime[6] = {2, 3, 5, 233, 331};
LL qmul(LL x, LL y, LL mod) { // ³Ë·¨·ÀÖ¹Òç³ö£¬ Èç¹ûp * p²»±¬LLµÄ»°¿ÉÒÔÖ±½Ó³Ë£» O(1)³Ë·¨»òÕß×ª»¯³É¶þ½øÖÆ¼Ó·¨


    return (x * y - (long long)(x / (long double)mod * y + 1e-3) *mod + mod) % mod;
    /*
    LL ret = 0;
    while(y) {
        if(y & 1)
            ret = (ret + x) % mod;
        x = x * 2 % mod;
        y >>= 1;
    }
    return ret;
    */
}
LL qpow(LL a, LL n, LL mod) {
    LL ret = 1;
    while(n) {
        if(n & 1) ret = qmul(ret, a, mod);
        a = qmul(a, a, mod);
        n >>= 1;
    }
    return ret;
}

bool Miller_Rabin(LL p) {
    if(p < 2) return 0;
    if(p != 2 && p % 2 == 0) return 0;
    LL s = p - 1;
    while(!(s & 1)) s >>= 1;
    for(int i = 0; i < 5; ++ i) {
        if(p == prime[i]) return 1;
        LL t = s, m = qpow(prime[i], s, p);
        while(t != p - 1 && m != 1 && m != p - 1) {
            m = qmul(m, m, p);
            t <<= 1;
        }
        if(m != p - 1 && !(t & 1)) return 0;
    }
    return 1;
}

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

void dismt(){
    for(int i = 0; i < n; ++ i){
        int x = a[i];
        int now = 2;
        while(x > 1){
            if(x > 10000 && Miller_Rabin(x)){
                rec[x] ++;
                break;
            }
            int tmp = x;
            while(x % now == 0){
                x /= now;
            }
            if(tmp != x){
                rec[now] ++;
            }
            now ++;
        }
    }
}

int main(){
    while(~scanf("%d", &n)){
        rec.clear();
        int g;
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            if(i == 0){
                g = a[i];
            }
            else {
                g = gcd(g, a[i]);
            }
        }
        if(g != 1){
            for(int i = 0; i < n; ++ i){
                a[i] /= g;
            }
        }
        dismt();
        int maxx = -1;
        int recp = -1;
        for(auto i = rec.begin(); i != rec.end(); ++ i){
            if(i->second > maxx){
                maxx = i->second;
                recp = i->first;
            }
            //printf("rec[%d] = %d\n", i->first, i->second);
        }
        int cnt1 = 0;
        for(int i = 0; i < n; ++ i){
            if(a[i] == 1){
                cnt1 ++;
            }
        }
        if(n == cnt1){
            printf("-1\n");
            continue;
        }
        else {
            g = -1;
            for(int i = 0; i < n; ++ i){
                if(a[i] != 1){
                    if(g == -1){
                        g = a[i];
                    }
                    else {
                        g = gcd(g, a[i]);
                    }
                }
            }
            if(g > 1){
                printf("%d\n", cnt1);
                continue;
            }
            printf("%d\n", n - maxx);
        }
    }
    return 0;
}