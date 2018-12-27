#include<cstdio>
#include<math.h>
#include<cstring>
#define ll long long
#include<algorithm>
using namespace std;

ll p, a;

bool checkPrime(ll n)
{
    if(n % 2 == 0)return false;
    if(n == 1)return false;
    if(n == 2)return true;
    int aa = sqrt((long double)n);
    for(int i = 2; i < aa; i++)
        if(n % i == 0)return false;
    return true;
}

ll fast_pow(int p, int a)
{
    ll ans = 1;
    int m = p;
    while(p)
    {
        if(p & 1)ans = (ans * a) % m;
        a = (a * a) % m;
        p >>= 1;
    }
    return ans;
}

int main()
{
    while(~scanf("%d%d", &p, &a) && (p || a))
    {
        bool ans = false;
        if(checkPrime(p))ans = false;
        else if(fast_pow(p, a) == a)ans = true;
        if(ans)printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
