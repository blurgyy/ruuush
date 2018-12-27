#include<stdio.h>
int main()
{
    int n, l;
    int a[110], b[110];
    while(~scanf("%d%d", &n, &l))
    {
        int i, f = 0;
        for(i = 0; i < n; i++)
            scanf("%d", a + i);
        for(i = 0; i < n; i++)
            scanf("%d", b + i);
        int left = 0;
        int sa[110], sb[1000];
        for(i = 1; i < n; i++)
        {
            sa[i - 1] = a[i] - a[i-1];
            sb[i - 1] = b[i] - b[i-1];
        }
        sa[n - 1] = l - a[n - 1] + a[0];
        sb[n - 1] = l - b[n - 1] + b[0];
        while(f == 0)
        {
            for(i = 0; i < n; i++)
            {
                if(sa[i] != sb[left + i])break;

            }
            if(i == n)
            {
                f = 1;
                continue;
            }
            sb[n + left] = sb[left++];
            if(left > l + 10)break;
        }
        if(f == 0)printf("NO\n");
        else printf("YES\n");
/*        for(i = 0; i < n; i++)printf("%d ",sa[i]);
        printf("\n");
        for(i = 0; i < n; i++)printf("%d ",sb[i]);
        printf("\n");*/
    }
    return 0;
}
