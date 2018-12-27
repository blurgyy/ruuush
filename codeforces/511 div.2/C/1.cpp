#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long LL;
const int maxpri = 15000010;
const int maxp = 1000010;
const int maxn = 300010;
const int inf = 0x3f3f3f3f;

int n;
int a[maxn];
int totp;
int prm[maxp];
int p[maxn];
bool v[maxpri+1] = {0};
//pii cpont[maxn][10];    ///<prime, cnt>;
int cpont[maxn][10];
int cnt[maxp];

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

int init_prime(int n, int pri[]){
    int k = 0;
    int i,q;
    for(i = 2,q = sqrt(n)+1; i < q; i++){
        if(!v[i]){
            pri[k++] = i;
            for(int j = i<<1; j <= n; j+=i){
                v[j] = true;
            }
        }
    }
    for(;i <= n; i++){
        if(!v[i]){
            pri[k++] = i;
        }
    }
    printf("k = %d\n", k);
    return k;
}

bool dismantle(int pos){
    if(a[pos] == 1)return false;
    bool ret = false;
    int x = a[pos];
    int now = 2;
    while(x > 1){
        if(Miller_Rabin(x)){
            cpont[pos][p[pos]++] = x;
            return ret;
        }
        int tmp = x;
        while(x % now == 0){
            x /= now;
        }
        if(tmp != x){
            cpont[pos][p[pos]++] = now;
        }
        now ++;
    }
    //for(int i = 0; i < totp; ++ i){
    //    if(Miller_Rabin(x)){
    //        cpont[pos][p[pos]++] = x;
    //        return true;
    //    }
    //    int now = prm[i];
    //    int curcnt = 0;
    //    while(x % now == 0){
    //        //printf("x = %d, now = %d\n", x, now);
    //        curcnt ++;
    //        x /= now;
    //    }
    //    if(curcnt == 0)continue;
    //    ret = true;
    //    //cpont[pos][p[pos]++] = make_pair(now, curcnt);
    //    cpont[pos][p[pos]++] = now;
    //    cnt[i] ++;
    //    //printf("cnt[%d] = %d\n", i, cnt[i]);
    //    if(x == 1)break;
    //}
    //if(ret)printf("dismantled!\n");
    return ret;
}

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    //printf("%d %d %d\n", gcd(512, 1024), gcd(17, 14), gcd(588, 900));
    totp = init_prime(maxpri, prm);
    printf("%d\n", prm[970703]);
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            p[i] = cnt[i] = 0;
        }
        //memset(p, 0, sizeof(p));
        //memset(cnt, 0, sizeof(cnt));
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
        for(int i = 0; i < n; ++ i){
            dismantle(i);
        }

        int cnt_1 = 0;
        for(int i = 0; i < n; ++ i){
            cnt_1 += (a[i] == 1);
        }
        if(cnt_1 == n){
            printf("-1");
            continue;
        }
        else {
            int gg = -1;
            if(cnt_1){
                for(int i = 0; i < n; ++ i){
                    if(a[i] != 1){
                        if(gg == -1){
                            gg = a[i];
                        }
                        else {
                            gg = gcd(gg, a[i]);
                        }
                    }
                }
                if(gg != 1){
                    printf("%d\n", cnt_1);
                    continue;
                }
            }
            {
                int maxx = -inf;
                int rec = -1;
                for(int i = 0; i < maxp; ++ i){
                    if(cnt[i] > maxx){
                        maxx = cnt[i];
                        rec = prm[i];
                    }
                }
                if(rec == -1){
                    printf("wtf\n");
                    continue;
                }
                else {
                    int ans = 0;
                    for(int i = 0; i < n; ++ i){
                        for(int j = 0; j < p[i]; ++ j){
                            if(cpont[i][j] == rec){
                                ans ++;
                                continue;
                            }
                        }
                    }
                    ans = n - ans;// - cnt_1;
                    //ans += cnt_1;
                    printf("%d\n", ans);
                    continue;
                }
            }
        }

        //for(int i = 0; i < n; ++ i){
        //    printf("%d(%d): ", a[i], p[i]);
        //    for(int j = 0; j < p[i]; ++ j){
        //        printf("(%d, %d) ", cpont[i][j], cpont[i][j]);
        //    }
        //    printf("\n");
        //}
    }
    return 0;
}