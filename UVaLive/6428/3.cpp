#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

ll a, b, x, y, s;

ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a%b);
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
    while(~scanf("%lld%lld%lld", &a, &b, &s))
    {
        if(a == 0 && b == 0)
        {
            if(s == 0)printf("YES\n");
            else printf("NO\n");
            continue;
        }
        if(a == s || b == s)
        {
            printf("YES\n");
            continue;
        }
        ll g = exgcd(a, b, x, y);
        if(s % g)
        {
            printf("NO\n");
            continue;
        }
        a /= g;
        b /= g;
        s /= g;
        g = gcd(a, b);
        bool ans = false;
        x = (x%b) * (s/g % b);
        x = (x % b + b) % b;
        y = (s - (a*x)) / b;
        while(y > 0)
        {
            if(x > 0 && y > 0 && gcd(x, y) == 1)
            {
                ans = true;
                break;
            }
            x += b/g;
            y -= a/g;
        }
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
