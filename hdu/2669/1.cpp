#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;

ll a, b;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll ret = exgcd(b, a%b, x, y);
    ll t = x;
    x = y;
    y = t - a/b * y;
    return ret;
}

int main()
{
    while(~scanf("%lld%lld", &a, &b))
    {
        ll x, y;
        ll gcd = exgcd(a, b, x, y);
        if(gcd != 1)printf("sorry\n");
        else
        {
            while(x < 0)x += b, y -= a;
            printf("%lld %lld\n", x, y);
        }
    }
    return 0;
}
