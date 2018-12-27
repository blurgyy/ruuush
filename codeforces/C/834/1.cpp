#include<cstdio>
#include<cmath>
#include<map>
#include<algorithm>
#define LL long long
#define maxn 100010
using namespace std;

int n, a, b;
map<int, int> faca, facb;
int p;
int Case = 1;

LL prime[6] = {2, 3, 5, 233, 331};
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

/**
bool check_Prime(int x)
{
    if(x == 1)return false;
    if(x == 2)return true;
    if(!(x&1))return false;
    int tp = sqrt(x);
    for(int i = 2; i <= tp; i++)
        if(x % i == 0)return false;
    return true;
}
*/

void divi(int a, int b)
{
    if(Miller_Rabin(a))faca[a]++;
    //printf("(1)");
    else{
        for(int i = 2; a > 1 && !Miller_Rabin(a); i++){
            while(a % i == 0){
                faca[i]++;
                a /= i;
            }
        }
        if(Miller_Rabin(a) && a > 1)faca[a]++;
    }
    if(Miller_Rabin(b))facb[b]++;
    //printf("(2)");
    else{
        for(int i = 2; b > 1 && !Miller_Rabin(b); i++){
            while(b % i == 0){
                facb[i] ++;
                b /= i;
            }
        }
        if(Miller_Rabin(b) && b > 1)facb[b]++;
    }
}

void out()
{
    map<int, int>::iterator i;
    for(i = faca.begin(); i != faca.end(); i++)
        printf("faca[%d] = %d\n", (*i).first, (*i).second);
    printf("\n");
    for(i = facb.begin(); i != facb.end(); i++)
        printf("facb[%d] = %d\n", (*i).first, (*i).second);
}

void init()
{
    faca.clear();
    facb.clear();
    p = 0;
}

int main()
{
    while(~scanf("%d", &n))
    {
        while(n--)
        {
            init();
            bool ans = true;
            bool esc = false;
            scanf("%d%d", &a, &b);

            divi(a, b);
            //printf("(3)");
            //out();
            map<int, int>::iterator i = faca.begin(), j = facb.begin();
            while(i != faca.end() && j != facb.end())
            {
                if((*i).first != (*j).first){
                    ans = false;
                    esc = true;
                    break;
                }
                else{
                    /*while((*i).second && (*j).second){
                        if((*i).second > (*j).second) {
                            (*i).second -= 2;
                            (*j).second --;
                        }
                        else{
                            (*i).second --;
                            (*j).second -= 2;
                        }
                    }*/
                    if(max((*i).second, (*j).second) - min((*i).second, (*j).second) > min((*i).second, (*j).second))
                    {
                        ans = false;
                        esc = true;
                        break;
                    }
                    (*i).second %= 3;
                    (*j).second %= 3;
                    if((*i).second == (*j).second && (*i).second != 0)
                    {
                        ans = false;
                        esc = true;
                        break;
                    }
                    /*if((*i).second || (*j).second)
                    {
                        ans = false;
                        esc = true;
                        break;
                    }*/
                    i++;
                    j++;
                }
            }
            if(esc);
            else if(i != faca.end() || j != facb.end())ans = false;

            //printf("\n");

            if(ans)printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}


/**

956752413 952678161
(NO)

641239463 512853521
(yes)

*/
