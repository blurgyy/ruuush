#include<cstdio>
#include<cstdlib>
#include<time.h>

int main()
{
    srand(time(NULL));
    int n = 200000;
    while(n--)
        printf("%d\n", rand() % 100000000 + 1);
    return 0;
}
