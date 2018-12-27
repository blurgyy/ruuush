#include<stdio.h>
#define maxn 100010
struct friends
{
    int b[3] = {0};
    int g[3] = {0};
}sheep[maxn];
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int counter[maxn];
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        int i;
        for(i = 0; i < k; i++)
        {
            int b, g;
            scanf("%d%d", &b, &g);
            if(!sheep[b].b[1])
            {
                sheep[b].b[1] = g;
            }
            else sheep[b].b[2] = g;
            if(!sheep[g].g[1])sheep[g].g[1] = b;
            else sheep[g].g[2] = b;
        }

    }
}
