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

ll calc(int l, int r)
{
    ll sum = 0;
    for(int i = l; i <= r; i++)
        sum += a[i].value;
    return sum;
}

void init()
{
    for(int i = 0; i < n; i++)
    {
        a[i].index = i;
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
            sum += a[i].value;
        }
        if(sum & 1LL)printf("No\n");
        else
        {
            printf("Yes\n");
            ll finish = sum / 2;
            sort(a, a + n);
            ll s = a[1].value;
            int l = 1, r = 1;
            while(s < finish - 1)
                s += a[++r].value;
            while(s != finish - 1)
            {
                if(s > finish - 1)
                    s -= a[l++].value;
                else
                    s += a[++r].value;

                printf("s = %d\n", s);
                printf("l %d, r %d\n", l, r);
            }
            for(int i = 0; i < n; i++)
            {
                if(i == 0)printf("1");
                else if(a[i].index < l || a[i].index > r)printf(" -1");
                else printf(" 1");
            }
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
5
1 2 2 2 3
5
1 2 3 3 5
4
1 2 3 2
10
1 2 1 3 5 4 4 8 3 7
10
1 1 2 3 3 4 4 5 7 8
9
1 1 2 3 3 4 5 7 8


*/
