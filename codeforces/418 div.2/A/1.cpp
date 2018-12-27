#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 210
using namespace std;

int n, k;
int a[maxn], b[maxn];
int blank[maxn];

bool cmp(int a, int b)
{
    return a > b;
}

bool check()
{
    for(int i = 1; i < n; i++)
    {
        if(a[i] == 0 || a[i-1] == 0)continue;
        if(a[i] < a[i-1])return true;
    }
    return false;
}

int main()
{
    while(~scanf("%d%d", &n, &k))
    {
        memset(blank, 0, sizeof(blank));
        int p = 0;
        for(int i = 0; i < n; i++)
        {
            scanf("%d", a + i);
            if(a[i] == 0)blank[p++] = i;
        }
        for(int i = 0; i < k; i++)
            scanf("%d", b + i);
        if(check())
        {
            printf("Yes\n");
            continue;
        }
        sort(b, b + k, cmp);
        bool breaker = false;
        for(int i = 0; i < p; i++)
        {
            a[blank[i]] = b[i];
            if(check())
            {
                printf("Yes\n");
                breaker = true;
            }
            if(breaker)break;
        }
        if(breaker)continue;
        printf("No\n");
    }
    return 0;
}
