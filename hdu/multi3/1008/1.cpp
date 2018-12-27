#include<cstdio>
#include<algorithm>
#define ll long long
#define M 1000000007
using namespace std;

ll n, k;
ll Case = 1;

ll fp(ll a, ll b)
{
    ll ans = 1;
    while(b)
    {
        if(b&1)ans = (ans * a) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return ans;
}

int main()
{
    while(~scanf("%lld%lld", &n, &k))
    {
        n %= M;
        ll ans = fp(n, k);
        printf("Case #%lld: %lld\n", Case++, ans);
    }
    return 0;
}
