#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;

int main()
{
    double n, p;
    while(~scanf("%lf%lfd", &n, &p))
        printf("%.0lf\n", pow(p, 1.0/n));
    return 0;
}
