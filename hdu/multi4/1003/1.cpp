#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#define LL long long
#define pb push_back
using namespace std;

const int N = 1e6 + 7;
const int MOD = 998244353;

vector<int > V;
int not_prime[N];
LL sq[N];
LL l ,r, k;

LL prime[6] = {7, 3, 5, 233, 331};
LL qmul(LL x, LL y, LL mod) { // 乘法防止溢出， 如果p * p不爆LL的话可以直接乘； O(1)乘法或者转化成二进制加法


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



int pr()
{
    memset(not_prime, 0, sizeof(not_prime));
    for (LL i = 2; i < 1000000; i ++){
        if (!not_prime[i]){
            V.pb(i);
            if (i * i <= 1000000){
                for (LL j = i + i; j <= 1000000; j += i){
                    not_prime[j] = 1;
                }
            }
        }
    }
}

LL g(LL x)
{
    LL cnt;
    LL t = x;
    int i = 0;
    LL ans = 1;

    while(t != 1){
        if(t >= (LL)1e4 && Miller_Rabin(t)){
            ans = (ans * (k + 1)) % MOD;
            break;
        }
        cnt = 0;
        while(t % V[i] == 0){
            cnt ++;
            t /= V[i];
            //printf("%d %lld\n", V[i], t);
        }
        i ++;
        ans = (ans * (cnt * k + 1)) % MOD;
    }

    return ans;
}



int main()
{
    int ncase;
    ///1
    pr();
    /*k = 1;
    for(int i = 1; i <= 100; i ++){
        printf("%d %lld\n", i, g(i));
    }*/
    scanf("%d", &ncase);
    while(ncase --){
        LL ans = 0;

        scanf("%lld%lld%lld", &l, &r, &k);
        for(LL i = l; i <= r; i ++){
                //printf("g(%lld) = %lld\n", i, g(i));
            ans = (ans + g(i)) % MOD;
            //printf("i = %lld\n", i);
            //printf("%lld\n", ans);
        }
        printf("%lld\n", ans);
    }

    return 0;
}


/**

99999999990 99999999999 1

*/
