#include<stdio.h>
#include<string.h>
int main()
{
    char res[1010][3][15], t1[15], t2[15];
    int n;
    scanf("%s%s", res[0][1], res[0][2]);
        scanf("%d", &n);
        int i;
        for(i = 1; i <= n; i++)
        {
            scanf("%s%s", t1, t2);
            if(strcmp(res[i-1][1], t1) == 0)
            {
                int j;
                for(j = 0; j < strlen(t2); j++)
                {
                    res[i][1][j] = t2[j];
                }
                for(j = 0; j < strlen(res[i-1][2]); j++)
                {
                    res[i][2][j] = res[i-1][2][j];
                }
            }
            else
            {
                int j;
                for(j = 0; j < strlen(t2); j++)
                {
                    res[i][2][j] = t2[j];
                }
                for(j = 0; j < strlen(res[i-1][1]); j++)
                {
                    res[i][1][j] = res[i-1][1][j];
                }
            }
        }
        for(i = 0; i <= n; i++)
            printf("%s %s\n", res[i][1], res[i][2]);
    return 0;
}
