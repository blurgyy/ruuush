#include<stdio.h>
#include<algorithm>
#define maxn 200010
using namespace std;

struct input
{
    int a;
    int b;
    int diff;
}money[maxn];

bool cmp(input a, input b)
{
    return a.diff > b.diff;
}

int main()
{
    int n, k;
    while(~scanf("%d%d", &n, &k))
    {
        int i;
        for(i = 0; i < n; i++)
            scanf("%d", &money[i].a);
        for(i = 0; i < n; i++)
        {
            scanf("%d", &money[i].b);
            money[i].diff = money[i].b - money[i].a;
        }
        sort(money, money + i, cmp);
        int ans = 0;
        for(i = 0; i < k || money[i].diff > 0; i++)
        {
            ans += money[i].a;
        }
        for(; i < n; i++)
        {
            ans += money[i].b;
        }
        printf("%d\n", ans);
    }
    return 0;
}
