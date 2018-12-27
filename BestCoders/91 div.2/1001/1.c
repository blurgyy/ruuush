#include<stdio.h>
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n, val[27][2];
        scanf("%d", &n);
        int i;
        for(i = 1 ; i <= n; i++)
        {
            scanf("%d%d", &val[i][0], &val[i][1]);
        }
        int j;
        for(i = 1; i <= n; i++)
        {
            for(j = 2 + i - 1; j <= n; j++)
            {
                if(val[j][0] < val[j-1][0])
                {
                    int c;
                    c = val[j][0];
                    val[j][0] = val[j-1][0];
                    val[j-1][0] = c;
                    c = val[j][1];
                    val[j][1] = val[j-1][1];
                    val[j-1][1] = c;
                }
            }
        }

        int count = 1;
        int sum = 0;
        for(i = 1; i <= n; i++)
        {
            if(val[i][0] < 0)continue;
            sum += val[i][0] * (((count + count - 1 + val[i][1]) * val[i][1]) / 2);
            count += val[i][1];
        }
        printf("%d\n", sum);
    }
    return 0;
}
