#include<cstdio>
#include<cstring>
#include<cmath>
#define maxn 20
#define ll long long

ll h[maxn] = {0};
ll b[maxn] = {0};
ll a[maxn] = {0};

int main()
{
    h[0] = 2;
    h[1] = 3;
    h[2] = 6;
    for(int i = 0; i < maxn; i++)
    {
        if(i >= 3)h[i] = 4*h[i-1] + 17*h[i-2] - 12*h[i-3] - 16;
        printf("h[%d] = %lld\n", i, h[i]);
    }
    for(int i = 1; i < maxn-5; i++)
    {
        b[i] = 3*h[i+1]*h[i];
        b[i] += 9*h[i+1]*h[i-1];
        b[i] += 9*h[i]*h[i];
        b[i] += 27*h[i]*h[i-1];
        b[i] -= 18*h[i+1];
        b[i] -= 126*h[i];
        b[i] -= 81*h[i-1];
        b[i] += 192;
        printf("b[%d] = %lld\n", i, b[i]);
    }
    for(int i = 1; i < maxn-5; i++)
    {
        a[i] = sqrt(b[i] + (ll)pow(4, i));
        printf("a[%d] = %lld\n", i, a[i]);
    }
    for(int i = 2; i < 10; i++)
        printf("%.15llf\n",(double)a[i+1]/a[i]);
    returns 0;
}
