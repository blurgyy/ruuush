#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
#define ll long long
using namespace std;

int n;

struct node
{
    int value;
    int index;
}a[maxn];

bool operator < (node a, node b)
{
    return a.value < b.value;
}

int ans[maxn];
ll sum;

void init()
{
    for(int i = 0; i < n; i++)
    {
        a[i].index = 0;
        a[i].value = 0;
    }
    memset(ans, 0, sizeof(ans));
    sum = 0;
}

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &a[i].value);
            a[i].index = i;
            sum += a[i].value;
        }
        if(sum & 1LL)printf("No\n");
        else
        {
            printf("Yes\n");
            ll finish = sum / 2;
            sort(a, a + n);
            ll s = 0;
            int i = 0;
            int p0 = n/2 - 1, p = n/2;
            while(s < finish)
            {
                if(p >= n-1)s += a[p0--].value;
                else if(p0 <= 0)s += a[p++].value;
                else if(i & 1)s += a[p0--].value;
                else s += a[p++].value;
                i++;
            }
/*
            printf("p0 = %d, p = %d\n", p0, p);

            printf("s = %d\n", s);

            for(int i = 0; i < n; i++)
                printf("%d\n", a[i].index);
*/
            for(int i = 0; i < n; i++)
                if(i <= p0 || i >= p)
                    ans[a[i].index] = 1;
                else ans[a[i].index] = -1;
            for(int i = 0; i < n; i++)
                if(i == 0)printf("%d", ans[i]);
                else printf(" %d", ans[i]);
            printf("\n");
        }
    }
    return 0;
}

/**

9
1 1 2 1 2 2 1 4 4
9
1 1 1 1 2 2 2 4 4

*/
