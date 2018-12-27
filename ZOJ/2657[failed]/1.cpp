#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

ll x, y, m, n, l;

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

int bs(int left, int right, ll t1, ll t2, ll gcd)
{
    if(left >= right)return right;
    int mid = (left + right)>>1;
    if(t1 + mid * (n/gcd) < t2 - mid * (m/gcd))return bs(mid + 1, right, t1, t2, gcd);
    return bs(left, mid, t1, t2, gcd);
}

int main()
{
    while(~scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l))
    {
        ll t1, t2 , t3, t4, X, Y;
        ll gcd = exgcd(m, n, X, Y);
        ll pos_dist = abs(x-y);
        ll neg_dist = l - pos_dist;
        if(pos_dist % gcd)
        {
            printf("Pat\n");
            continue;
        }
        printf("X = %lld, Y = %lld, gcd = %lld\n", X, Y, gcd);
        t1 = X * neg_dist / gcd;
        t2 = Y * neg_dist / gcd;
        int tmp = bs(0, 100000000, t1, t2, gcd);
        t3 = X * pos_dist / gcd;
        t4 = Y * pos_dist / gcd;
        int tmptmp = bs(0, 100000000, t3, t4, gcd);
        printf("t1 = %lld, t2 = %lld, t3 = %lld, t4 = %lld\n", t1, t2, t3, t4);
        ll ans;
        ans = min(abs(t1 + tmp * (n/gcd)), abs(t3 + tmptmp * (n/gcd)));
        printf("%lld\n", ans);
    }
    return 0;
}

/**

1 2 3 4 5
10 1 2 2 20

*/
