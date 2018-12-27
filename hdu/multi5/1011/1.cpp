#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;

int t, n, k;
int a[maxn];

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; i++)
            scanf("%d", a + i);
        sort(a, a + n);
        int cnt = 1;
        for(int i = n-1; i > 0; i--)
        {
            if(a[i] - a[i-1] <= k)cnt++;
            else break;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
