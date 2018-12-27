#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

int k;
ll A, B;
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

int main()
{
    scanf("%d", &k);
    while(k--)
    {
        scanf("%lld/%lld", &A, &B);
        ll gcd = exgcd(A, B, x, y);
        if(gcd != 1)
        {
            printf("%lld/%lld\n", A/gcd, B/gcd);
            continue;
        }
        if(A == 1)
        {
            printf("1/%lld\n", B-1LL);
            continue;
        }
        ll c1, d1, c2, d2;
        c1 = -y + A;
        d1 = x + B;
        c2 = y + A;
        d2 = -x + B;

        if(d1 >= B)
        {
            x = d2;
            y = c2;
        }
        else if(d2 >= B)
        {
            x = d1;
            y = c1;
        }
        else if(abs(d1*c1) < abs(d2*c2))
        {
            x = d2;
            y = c2;
        }
        else
        {
            x = d1;
            y = c1;
        }

        /*if(tx*ty < x*y)*/printf("%lld/%lld\n", abs(y), abs(x));
        //else printf("%lld/%lld\n", -ty, tx);
    }
    return 0;
}
