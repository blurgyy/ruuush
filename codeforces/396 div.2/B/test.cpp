#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 100010

bool cmp(int x, int y)
{
    return x > y;
}

int check(int a, int b, int c)
{
    if(a + b > c)return 1;
    else return 0;
}

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int f = 0;
        int seg[maxn];
        int a = 0, b = 1, c = 2;
        int i;
        for(i = 0; i < n; i++)
            scanf("%d", &seg[i]);
        sort(seg, seg + n, cmp);
        for(i = 0; i < n - 2; i++)
        {
            f = check(seg[i+2], seg[i+1], seg[i]);
            if(f == 1)break;
        }
        if(f == 1)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
