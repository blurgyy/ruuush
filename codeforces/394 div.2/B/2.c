//没有考虑到各个两元素之间的差的排列顺序不同。。。
//看不懂算了反正这个错了

#include<stdio.h>
int main()
{
    int n, l;
    int a[110], b[110], c[110];
    while(~scanf("%d%d", &n, &l))
    {
        int i, f = 0;
        for(i = 0; i < n; i++)
        {
            scanf("%d",a + i);
        }
        for(i = 0; i < n; i++)
        {
            scanf("%d", b + i);
        }
        int add;
        for(add = -l-3; add <= l+3; add++)
        {
            f = 0;
            for(i = 0; i < n; i++)
            {
                c[i] = b[i] + add;
                while(c[i] >= l)
                {
                    c[i] -= l;
                }
                while(c[i] < 0)
                {
                    c[i] += l;
                }
            }
            for(i = 0; i < n; i++)
            {
                if(c[i] == a[i])continue;
                f = 1;
                break;
            }
            if(f == 0) break;
        }
        if(f == 0)printf("YES\n");
        else printf("NO\n");
        printf("c[]:\t");
        for(i = 0; i < n; i++)
            printf("%d ",c[i]);
            printf("\n");
        printf("a[]\t");
        for(i = 0; i < n; i++)
            printf("%d ",a[i]);
        printf("\n\n");
    }
    return 0;
}
