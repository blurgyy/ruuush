#include<stdio.h>
#define maxn 200010
int a[maxn], n;
void swap(int x, int y)
{
    int c;
    c = a[x];
    a[x] = a[y];
    a[y] = c;
}
int main()
{
    while(scanf("%d", &n) != EOF)
    {
        int i;
        for(i = 1; i <= n; i++)
        {
            scanf("%d", a + i);
        }
        int time = n / 2;
        if(time % 2 == 0)
        {
            if(n % 2 == 0)
            {
                for(i = n / 2 - 1; i > 0; i -= 2)
                {
                    swap(i, n - i + 1);
                }
            }
            else
            {
                for(i = n / 2 - 1; i > 0; i -= 2)
                {
                    swap(i, n - i + 1);
                }
            }
        }
        else
        {
            if(n % 2 == 0)
            {
                for(i = n / 2; i > 0; i -= 2)
                {
                    swap(i, n - i + 1);
                }
            }
            else
            {
                for(i = n / 2; i > 0; i -= 2)
                {
                    swap(i, n - i + 1);
                }
            }
        }
        for(i = 1; i <= n; i++)
            if(i == 1)printf("%d", a[i]);
            else printf(" %d", a[i]);
        printf("\n");
    }
    return 0;
}
