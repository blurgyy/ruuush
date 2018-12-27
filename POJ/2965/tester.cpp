#include<cstdio>
#include<stdlib.h>
#include<algorithm>
#include<time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    int cases = 80;
    while(cases--)
    {
        int i, t = 4;
        while(t--)
            printf("%c", rand()%2 == 1 ? '+' : '-');
        printf("\n");
    }
    return 0;
}
