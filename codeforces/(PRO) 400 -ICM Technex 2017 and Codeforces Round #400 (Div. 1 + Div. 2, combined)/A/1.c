#include<stdio.h>
#include<string.h>
int max(int a, int b)
{
    return a > b ? a : b;
}
int main()
{
    char na[15], me[15], t1[15], t2[15];
    while(~scanf("%s%s", na, me))
    {
        char res[2010][15];
        int n;
        scanf("%d", &n);
        int i;
        for(i = 1; i <= n; i++)
        {
            scanf("%s%s", t1, t2);
            if(i == 1)
            {
                if(strcmp(na, t1) == 0)
                {
                    int j;
                    for(j = 0; j < strlen(na); j++)
                    {
                        res[2*i-1][j] = t2[j];
                    }
                    for(j = 0; j < max(strlen(t2), strlen(me)); j++)
                    {
                        res[i*2][j] = me[j];
                    }
                }
                else
                {
                    int j;
                    for(j = 0; j < strlen(me); j++)
                    {
                        res[2*i-1][j] = t1[j];
                    }
                    for(j = 0; j < max(strlen(t2), strlen(na)); j++)
                    {
                        res[i*2][j] = na[j];
                    }
                }
            }
            else
            {
                if(strcmp(res[(i-1)*2-1], t1) == 0)
                {
                    int j;
                    for(j = 0; j < strlen(res[(i-1)*2-1]); j++)
                    {
                        res[2*i-1][j] = t2[j];
                    }
                    for(j = 0; j < max(strlen(t2), strlen(res[(i-1)*2])); j++)
                    {
                        res[i*2][j] = res[(i-1)*2][j];
                    }
                }
                else
                {
                    int j;
                    for(j = 0; j < strlen(res[(i-1)*2]); j++)
                    {
                        res[2*i-1][j] = t1[j];
                    }
                    for(j = 0; j < max(strlen(t2), strlen(res[(i-1)*2-1])); j++)
                    {
                        res[i*2][j] = res[(i-1)*2-1][j];
                    }
                }
            }
        }
        for(i = 1; i <= (2 * n); i += 2)
        {
            printf("%s %s\n", res[i], res[i+1]);
        }
    }
    return 0;
}
