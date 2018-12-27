#include<cstdio>
#include<cstring>
#include<cmath>
#include<tgmath.h>
#include<algorithm>
#define ll long long
using namespace std;

int n;
ll a, b;

int main()
{
    while(~scanf("%d", &n))
    {
        while(n--)
        {
            scanf("%lld%lld", &a, &b);
            ll prod = a * b;
            double temp = cbrt((double)prod);
            if(temp - 1 == 0)printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
