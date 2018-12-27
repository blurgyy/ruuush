#include<cstdio>
#include<map>
#include<cstring>
#include<algorithm>
#define maxn 200010
#define ll long long
using namespace std;

int T, n, m;
ll a[maxn];
int sq[maxn] = {0};

int main()
{
    scanf("%d", &T);
    int t = 1, p = 1;
    while(t <= 3*maxn)
    {
        for(; p <= t && p < maxn; p++)
            sq[p] = t;
        t <<= 1;
    }
    printf("%d\n", sq[maxn-1]);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++)
            scanf("%lld", a + i);
        for(int i = 0; i < m; i++)
        {
            for(int j = 2; j <= n; j++)
                a[j] = a[j]^a[j-1];
        }
        for(int i = 0; i < n; i++)
            if(i == 0)printf("%lld", a[i]);
            else printf(" %lld", a[i]);
        printf("\n");
    }
    return 0;
}
