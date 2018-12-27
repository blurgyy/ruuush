#include<stdio.h>
int main()
{
    int n, x;
    while(~scanf("%d%d", &n, &x))
    {
        if(x == 1)
        {
            if(n % 2 == 0)
            {
                if(n % 6 == 2)printf("2\n");
                else if(n % 6 == 4)printf("0\n");
                else printf("1\n");
            }
            else
            {
                if(n % 6 == 1)printf("0\n");
                else if(n % 6 == 3)printf("1\n");
                else printf("2\n");
            }
        }
        else if(x == 2)
        {
            if(n % 2 == 1)
            {
                if(n % 6 == 1)printf("2\n");
                else if(n % 6 == 3)printf("0\n");
                else printf("1\n");
            }
            else
            {
                if(n % 6 == 0)printf("2\n");
                else if(n % 6 == 4)printf("1\n");
                else printf("0\n");
            }
        }
        else
        {
            if(n % 2 == 1)
            {
                if(n % 6 == 5)printf("0\n");
                else if(n % 6 == 3)printf("2\n");
                else printf("1\n");
            }
            else
            {
                if(n % 6 == 0)printf("0\n");
                else if(n % 6 == 2)printf("1\n");
                else printf("2\n");
            }
        }
    }
}
