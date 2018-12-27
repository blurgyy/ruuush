#include<stdio.h>
#define maxn 100010
int main()
{
    int n, i, temp;
    while(~scanf("%d", &n))
    {
        int snack[maxn] = {0};
        int tag = 1, f = 0, j;
        for(i = 1; i <= n; i++)
        {
            scanf("%d", &temp);
            snack[n+1-temp] = temp;
            int k;
            for(j = tag, k = 0; snack[j] == n + 1 - j; j++, tag++, k++)
            {
                if(snack[j] != 0)
                {
                    if(k == 0) printf("%d", snack[j]);
                    else printf(" %d", snack[j]);
                }
            }
            printf("\n");
        }
    }
    return 0;
}
