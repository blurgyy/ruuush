#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;

int t;
ll s, e, a, b, c;
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
        scanf("%lld%lld%lld%lld", &s, &e, &a, &b);
        ll gcd = abs(exgcd(a, b, x, y));
        //printf("x = %lld, y = %lld\n", x, y);
        ll m = abs(s-e);
        if(m % gcd != 0)
        {
            printf("-1\n");
            continue;
        }
        x *= m/gcd;
        y *= m/gcd;
        printf("%d %d\n", x, y);
        ll ans1 = step();
        ll X = x, Y = y;
        x += (m/gcd)*b;
        y -= (m/gcd)*a;
        while(ans1 > step())
        {
            ans1 = min(ans1, step());
            x += (m/gcd)*b;
            y -= (m/gcd)*a;
        }
        x = X;
        y = Y;
        ll ans2 = step();
        x -= (m/gcd)*b;
        y += (m/gcd)*a;
        while(ans2 > step())
        {
            ans2 = min(ans2, step());
            x -= (m/gcd)*b;
            y += (m/gcd)*a;
        }
        printf("%lld\n", min(ans1, ans2));
    }
    return 0;
}
