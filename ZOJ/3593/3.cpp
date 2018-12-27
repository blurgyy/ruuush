#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;

int t;
ll A, B, a, b;
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
    scanf("%d", &t);
    while(t--)
    {
        scanf("%lld%lld%lld%lld", &A, &B, &a, &b);
        ll gcd = exgcd(a, b, x, y);
        ll m = abs(A-B);
        if(m % gcd)
        {
            printf("-1\n");
            continue;
        }

    }
}
