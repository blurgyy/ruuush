#include<cstdio>
#include<algorithm>
#define maxn 200010
using namespace std;

int main()
{
    int n;
    int a[maxn] = {0};
    int dif[maxn] = {0};
    while(~scanf("%d", &n))
    {
        int i;
        for(i = 0; i < n; i++)
            scanf("%d", a + i);
        sort(a, a + i);
        for(i = 0; i < n - 1; i++)
        {
            dif[i] = a[i+1] - a[i];
        }
    }
    return 0;
}
