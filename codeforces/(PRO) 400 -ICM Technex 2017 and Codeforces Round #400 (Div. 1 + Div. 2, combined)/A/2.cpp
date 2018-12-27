#include<stdio.h>
#include<string.h>
void write(char source[], char targ[])
{
    int len = strlen(source);
    int i;
    for(i = 0; i < len; i++)
    {
        targ[i] = source[i];
    }
    targ[i] = 0;
}
int main()
{
    char res[1010][3][15];
    scanf("%s%s", res[0][1], res[0][2]);
    char t1[15], t2[15];
    int n;
    scanf("%d", &n);
    int i;
    for(i = 1; i <= n; i++)
    {
        scanf("%s%s", t1, t2);
        if(strcmp(res[i-1][1], t1) == 0)
        {
            write(t2, res[i][1]);
            write(res[i-1][2], res[i][2]);
        }
        else
        {
            write(res[i-1][1], res[i][1]);
            write(t2, res[i][2]);
        }
    }
    for(i = 0; i <= n; i++)
    {
        printf("%s %s\n", res[i][1], res[i][2]);
    }
    return 0;
}
