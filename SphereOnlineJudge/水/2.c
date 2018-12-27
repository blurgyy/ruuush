//À´×ÔSPOJ
//TLEÁË
#include<stdio.h>
#include<math.h>
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        int i, count = 0;
        for(i = a; i <= b; i++)
        {
            int j;
            if(i == 1)continue;
            int lim = (int)sqrt(i) + 1;
            for(j = 2; j < lim; j++)
            {
                if(i % j == 0)break;
            }
            if(j == lim)
            {
                if(i == a)printf("%d", i);
                else printf(" %d", i);
            }
        }
        printf("\n");
    }
    return 0;
}
