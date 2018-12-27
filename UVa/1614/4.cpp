#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
#define ll long long
using namespace std;

int n;
int ans[maxn];
ll sum;

struct node
{
    int val;
    int ind;
}a[maxn];

bool operator < (node a, node b)
{
    return a.val < b.val;
}

void init()
{
    for(int i = 0; i < n; i++)a[i].ind = i;
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
            scanf("%d", &a[i].val);
            sum += a[i].val;
        }
        if(sum & 1)
        {
            printf("No\n");
            continue;
        }
        printf("Yes\n");
        sort(a, a + n);
        ll cur = 0;
        int p = n-1;
        while(p >= 0)
        {
            if(cur < 0)
            {
                cur += a[p].val;
                ans[a[p].ind] = 1;
            }
            else
            {
                cur -= a[p].val;
                ans[a[p].ind] = -1;
            }
            p--;
        }
        for(int i = 0; i < n; i++)
            if(i == 0)printf("%d", ans[i]);
            else printf(" %d", ans[i]);
        printf("\n");
    }
    return 0;
}
