#include<cstdio>
#include<stdlib.h>
#include<cmath>
#include<time.h>
#include<algorithm>
using namespace std;

int main()
{
    srand(time(NULL));
    int n, d;
    int t = 80;
    while(t--)
    {
        n = rand()%30 + 1;
        d = rand()%100 + 1;
        printf("%d %d\n", n, d);
        while(n--)
        {
            printf("%.0lf %d\n", (rand()%100 + 1) * pow(-1, rand()%2 + 1), rand()%60 + 1);
        }
    }
    return 0;
}
