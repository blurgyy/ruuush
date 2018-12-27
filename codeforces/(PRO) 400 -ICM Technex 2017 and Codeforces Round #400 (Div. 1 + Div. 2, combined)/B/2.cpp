#include<stdio.h>
#include<math.h>
#define maxn 100010
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
    int color[maxn], n;
    while(~scanf("%d", &n))
    {
        int i, counter;
        for(i = 2; i <= n + 1; i++)
        {
            if(isprime(i))color[i] = 1;
            else color[i] = 2;
        }
        if(n < 3)counter = 1;
        else counter = 2;
        printf("%d\n", counter);
        for(i = 2; i <= n + 1; i++)
        {
            if(i == 2)printf("%d", color[i]);
            else printf(" %d", color[i]);
        }
        printf("\n");
    }
}
