#include<stdio.h>
#define maxn 1010

int table[maxn][maxn];

int yes(int j, int l, int r)
{
    int i;
    for(i = l; i < r; i++)
    {
        if(table[i][j] > table[i+1][j])return 0;
    }
    return 1;
}

int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m))
    {
        int i, j;
        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= m; j++)
            {
                scanf("%d", table[i] + j);
            }
        }
        int k;
        scanf("%d", &k);
        while(k--)
        {
            int l, r, f = 1;
            scanf("%d%d", &l, &r);
            for(j = 1; j <= m; j++)
            {
                for(i = l; i <= r; i++)
                {
                    if(yes(j, l, r))
                    {
                        f = 0;
                        printf("YES\n");
                        break;
                    }
                }
                if(!f)break;
            }
            if(f)printf("NO\n");
        }
    }
    return 0;
}
