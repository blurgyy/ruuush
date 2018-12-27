#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

int T;
ll h, l;
ll base;
int Case = 1;

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%lld%lld", &h, &l);
        int cnt = 0;
        ll tmp = l;
        base = 0;
        for(ll i = 1; i < tmp; i *= 2)
        {
            base += i;
            cnt++;
        }
        //printf("%lld\n", base);
        //printf("%d\n", cnt);
        ll ans = base;
        ans += (h-cnt+1) * l;
        printf("Case %d: %lld\n", Case++, ans);
    }
    return 0;
}
