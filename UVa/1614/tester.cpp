#include<cstdio>
#include<cstdlib>
#include<time.h>

int main()
{
    srand(time(NULL));
    int t = 300;
    while(t--)
    {
        int n = rand() % 10 + 5;
        printf("%d\n", n);
        for(int i = 1; i <= n; i++)
            printf("%d ", rand() % i + 1);
        printf("\n");
    }
    return 0;
}
