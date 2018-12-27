#include<stdio.h>
#include<algorithm>
#define maxn 100010
using namespace std;
bool cmp(int x, int y)
{
    return x > y;
}
int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int seg[maxn];
        bool flag = false;
        int i;
        for(i = 0; i < n; i++)
        {
            scanf("%d", &seg[i]);
        }
        sort(seg, seg + n, cmp);
        for(i = 0; i < n - 2; i++)
        {
            if(seg[i] < seg[i+1] + seg[i+2])
            {
                flag = true;
                break;
            }
        }
        if(flag)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
