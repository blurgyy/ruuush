#include<stdio.h>
#include<string.h>
int min(int a, int b)
{
    return a < b ? a : b;
}
int maax(int a, int b)
{
    return a > b ? a : b;
}
char a[100000], b[100000];
int main()
{
    while(scanf("%s%s", a, b) != EOF)
    {
        int i, j, max = -1, count = 0;
        int len1 = min(strlen(a), strlen(b)), len2 = maax(strlen(a), strlen(b));
        if(len1 == strlen(a))
        {
            for(i = 0; i < len2; i++)
            {
                for(j = 0; j < len1;)
                {
                    while(a[j] == b[i] && j < len2)
                    {
                        b[i] = 0;
                        j++;
                    }
                }
            }
        }
        else
        {
            for(i = 0; i < len2; i++)
            {
                for(j = 0; j < len1;)
                {
                    while(b[j] == a[i] && j < len2)
                    {
                        b[i] = 0;
                        j++;
                    }
                }
            }
        }
        for(i = 0; i < len2; i++)
        {
            if(len1 == strlen(a))
                if(b[i] != 0)count++;
                else
                {
                    if(count > max)max = count;
                    count = 0;
                }
            else
                if(a[i] != 0)count++;
                else
                {
                    if(count > max)max = count;
                    count = 0;
                }
        }
        printf("%d\n", max);
    }
    return 0;
}
