#include<cstdio>
#include<cstring>
#include<time.h>
#include<cstdlib>
#define ll long long

int main()
{
    srand(time(NULL));
    ll a, b;
    int t = 300;
    while(t--)
    {
        a = rand() * rand();
        b = a + 1000000;
        printf("%lld %lld %d\n", a, b, rand() % 10000000 + 1);
    }
    return 0;
}
