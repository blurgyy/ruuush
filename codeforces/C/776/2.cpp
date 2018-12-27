#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;

int n, k;
int a[maxn];
int pre[maxn];

void init()
{
    memset(pre, 0, sizeof(pre));
    //memset(a, 0, sizeof(a));
}

int main()
{
    while(~scanf("%d%d", &n, &k))
    {
        init();
        for(int i = 0; i < n; i++)
        {
            scanf("%d", a + i);
            if(!i)pre[i] = a[i];
            if(i)pre[i] = pre[i-1] + a[i];
        }
        for(int i = 0; i < n; i++)
            printf("%d\n", pre[i]);
        printf("\n");
    }
    return 0;
}
