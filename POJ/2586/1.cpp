#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;

int main()
{
    ll ans = 0;
    ll s, d;
    while(~scanf("%lld%lld", &s, &d))
    {
        int flag = 0;
        for(flag = 1; flag < 5; flag++)
            if(flag*d > s*(5-flag))break;
        if(s >= 4*d)flag = 0;
        if(flag == 0)printf("Deficit\n");
        else if(flag == 1)
        {
            ans = 10*s - 2*d;
            if(ans < 0)printf("Deficit\n");
            else printf("%lld\n", ans);
        }
        else if(flag == 2)
        {
            ans = 8*s - 4*d;
            if(ans < 0)printf("Deficit\n");
            else printf("%lld\n", ans);
        }
        else if(flag == 3)
        {
            ans = 6*(s - d);
            if(ans < 0)printf("Deficit\n");
            else printf("%lld\n", ans);
        }
        else if(flag == 4)
        {
            ans = 3 * s - 9 * d;
            if(ans < 0)printf("Deficit\n");
            else printf("lld\n", ans);
        }
        else printf("Deficit\n");
    }
    return 0;
}
