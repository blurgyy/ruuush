#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;

int t;
ll A, B, a, b;
ll x, y;

ll step()
{
    if(x*y < 0)return abs(x-y);
    return max(abs(x), abs(y));
}

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
    scanf("%d", &t);
    while(t--)
    {
        scanf("%lld%lld%lld%lld", &A, &B, &a, &b);
        ll gcd = exgcd(a, b, x, y);
        //printf("gcd = %lld\n", gcd);
        ll m = abs(A-B);
        if(m%gcd)
        {
            printf("-1\n");
            continue;
        }
        x *= m/gcd;
        y *= m/gcd;
        ll X = x, Y = y;
        ll ans = step();
        x -= b/gcd;
        y += a/gcd;
        while(ans > step())
        {
            ans = min(ans, step());
            x -= b/gcd;
            y += a/gcd;
        }
        x = X;
        y = Y;
        x += b/gcd;
        y -= a/gcd;
        //printf("x = %lld, y = %lld\n", x, y);
        while(ans > step())
        {
            ans = min(ans, step());
            x += b/gcd;
            y -= a/gcd;
        }
        //printf("ans = %lld\n", ans);
        printf("%lld\n", ans);
    }
    return 0;
}
