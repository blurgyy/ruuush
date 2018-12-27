#include<cstdio>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;

int main()
{
    srand(time(NULL));
    int t = 80;
    while(t--)
    {
        int i, j;
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
                if(rand() % 2 == 0)printf("b");
                else printf("w");
            printf("\n");
        }
    }
    return 0;
}
