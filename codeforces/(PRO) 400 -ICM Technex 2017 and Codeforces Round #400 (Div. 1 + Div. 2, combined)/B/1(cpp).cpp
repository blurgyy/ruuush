#include<stdio.h>
#include<math.h>
#include<algorithm>
#define maxn 100010
using namespace std;

int isprime(int x)
{
    int i;
    if(x == 2)return 1;
    for(i = 2; i <= (int)sqrt((double)x); i++)
    {
        if(x % i == 0)return 0;
    }
    return 1;
}

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int color[maxn] = {0};
        int i, maximum = 0;
        for(i = 2; i <= (n + 1)/2; i++)
        {
            if(isprime(i))
            {
                int j;
                for(j = 2 * i; j <= n + 1; j += i)
                    if(color[j] == color[i])
                    {
                        color[j] = color[i] + 1;
                        maximum = max(maximum, color[j]);
                    }
            }
        }
        printf("%d\n", maximum + 1);
        for(i = 2; i < n + 2; i++)
        {
            if(i == 2)printf("%d", color[i] + 1);
            else printf(" %d", color[i] + 1);
        }
        printf("\n");
    }
    return 0;
}
