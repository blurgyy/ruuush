#include<cstdio>
#include<string.h>
#include<algorithm>
using namespace std;

int pos(int n)
{
    if(n%2 == 1)return (n+1)/2;
    return n/2;
}

bool cmp(int a, int b)
{
    return a > b;
}

int cnt[300];

int main()
{
    int T;
    while(~scanf("%d", &T))
    {
        int n, r1, r2;
        while(T--)
        {
            memset(cnt, 0, 200 * sizeof(int));
            scanf("%d", &n);
            while(n--)
            {
                scanf("%d%d", &r1, &r2);
                int i = pos(r1), upp = pos(r2);
                if(i > upp)swap(i, upp);
                for(; i <= upp; i++)
                    cnt[i]++;
            }
            sort(cnt, cnt + 200, cmp);
            printf("%d\n", cnt[0]*10);
        }
    }
    return 0;
}
