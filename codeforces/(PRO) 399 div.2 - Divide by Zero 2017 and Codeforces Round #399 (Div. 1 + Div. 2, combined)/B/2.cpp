#include<stdio.h>
#include<algorithm>
#define maxn 100010
#define ll long long
using namespace std;
int main()
{
    ll n, m;
    int l, r;
    if(0)
    while(~scanf("%I64d%d%d", &n, &l, &r))
    {
        m = n;
        int i, mo[100];
        for(i = 0; m > 1; i++)
        {
            mo[i] = m % 2;
            m /= 2;
        }
        int j;
        for(j = 0; j < i; j++)
            printf("%d ", mo[j]);
        printf("\n");
    }
    printf("HOLY FUCK\n");
    return 0;
}
