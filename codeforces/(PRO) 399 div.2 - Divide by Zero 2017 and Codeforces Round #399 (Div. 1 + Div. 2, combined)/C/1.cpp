#include<stdio.h>
#include<algorithm>
#define maxn 100010
using namespace std;
int ranger[maxn], n, k, x;
int main()
{
    while(~scanf("%d%d%d", &n, &k, &x))
    {
        int i;
        if(k % 2 == 0)
        {
            for(i = 1; i <= n; i++)
            {
                scanf("%d", ranger + i);
            }
        }
        else
            for(i = 1; i <= n; i++)
            {
                int temp;
                scanf("%d", &temp);
                ranger[i] = temp ^ x;
            }

        for(i = 1; i <= n; i++)
            printf("%d ", ranger[i]);
        printf("\n");

        sort(ranger + 1, ranger + n + 1);
        printf("%d %d\n", ranger[1], ranger[n]);
    }
    return 0;
}
