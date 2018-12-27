#include<cstdio>

int T;
int a;

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &a);
        printf("%d\n", (a+3)/2);
    }
    return 0;
}
