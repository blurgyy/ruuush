#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

ll a, b, s;
ll x, y;

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
    y = t - (a/b) * y;
    return ret;
}

ll bs(ll left, ll right, ll x, ll y, ll a, ll b, ll gcd)
{
    printf("left %lld, right %lld\n", left, right);
    if(left >= right)return right;
    ll mid = (left + right)>>1;
    if(y - mid * a / gcd < a)return bs(left, mid, x, y, a, b, gcd);
    else return bs(mid + 1, right, x, y, a, b, gcd);
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
        ll gcd = exgcd(a, b, x, y);
        if(s % gcd)
        {
            printf("NO\n");
            continue;
        }
        a /= gcd;
        b /= gcd;
        s /= gcd;
        gcd = exgcd(a, b, x, y);
        x *= s/gcd;
        y *= s/gcd;
        bool ans = false;

        //printf("%lld, %lld\n", x, y);
        //if(x <= 0 || y <= 0)ans = false;
        /*else if(x > 0 && y > 0)ans = true;
        else if(x < 0 && y < 0)ans = false;*/
            /*
        if(x > 0)
        {
            ll t = bs(0, 1000000000, y, x, b, a, gcd);
            printf("t1 = %lld\n", t);
            if(y + t * a / gcd > 0)ans = true;
            else ans = false;
        }
        else if(y > 0)
        {
            ll t = bs(0, 1000000000, x, y, a, b, gcd);
            printf("t2 = %lld\n", t);
            if(x + t * b / gcd > 0)ans = true;
            else ans = false;
        }
        */
        if(x > 0 && x > b)
        {
            ll t = (x - b) / b;
            for(ll i = t-1; i <= t+1; i++)
            {
                if(x - i * b > 0 && y + i * a > 0)ans = true;
            }
            //printf("ttt = %lld\n", t);
        }
        if(ans == false)
            if(y > 0 && y > a)
            {
                ll t = (y - a) / a;
                for(ll i = t-1; i <= t+1; i++)
                {
                    if(x + i * b > 0 && y - i * a > 0)ans = true;
                }
                //printf("ttt = %lld\n", t);
            }
        printf("%lld %lld\n", x, y);
        printf("he : %lld\n", 998224353 * (-3138926905355103920) + 1000000007 * 5166159573771055057);
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/**

1 2 3
3 4 5
3 4 17
998224353 1000000007 10000000000000007
-3138926905355103920 5166159573771055057

*/
