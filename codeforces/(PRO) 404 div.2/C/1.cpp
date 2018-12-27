//FAILED :(


#include<stdio.h>
#include<algorithm>
#include<math.h>
#define ll long long
using namespace std;

double solve(double n, double m)
{
    double a = (m - 1)/2;
    double b = pow(a, 2);
    double c = 2 * n;
    double ans = a + pow(b + c, 0.5);
    return ans;
}

int main()
{
    ll n, m;
    while(~scanf("%I64d%I64d", &n, &m))
    {
        double N = n, M = m;
        ll ans = solve(N, M);
        ll i;
        for(ans - 10 < 1 ? i = 1 : i = ans - 10; i <= ans + 10; i++)
        {
            if(2 * n + m * i <= i * (i + 1))break;
        }
        printf("%I64d\n", i);
    }
    return 0;
}
