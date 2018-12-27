#include<stdio.h>
#include<algorithm>
#define maxn 100010
using namespace std;
int a[maxn];
int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int i, count = 0;
        for(i = 0; i < n; i++)
        {
            scanf("%d", a + i);
        }
        sort(a, a + n);
        int min = a[0], max = a[n-1];
        for(i = 0; i < n; i++)
        {
            if(a[i] == min || a[i] == max)count++;
        }
        printf("%d\n", n - count);
    }
    return 0;
}
