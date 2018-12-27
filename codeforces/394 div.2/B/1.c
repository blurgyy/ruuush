#include<stdio.h>
int main()
{
    int n, l;
    int a[110], b[110], s[110];
    while(scanf("%d%d", &n, &l)!=EOF)
{
    int i, j, f = 0;
    for(i = 0; i < n; i++)
    {
        scanf("%d", a + i);
        if(i == 0)continue;
        s[i] = a[i] - a[i-1];
    }
    s[0] = (l - a[n-1]) + a[0];

    for(i=0;i<n;i++)
        printf("%d ",s[i]);
    printf("\n");

    for(i = 0; i < n; i++)
    {
        scanf("%d", b + i);
        if(i == 0)continue;
        int jump = b[i] - b[i-1];
        for(j = 0; j < n; j++)
        {
            if(jump == s[j])
            {
                s[j] = 0;
                break;
            }
        }
        if(j == n)
        {
            f = 1;
            break;
        }
    }
    int jump = ((l - b[n-1]) + b[0]);
    for(j = 0; j < n; j++)
    {
        if(jump == s[j])
        {
            s[j] = 0;
            break;
        }
    }
    if(f == 0) printf("YES\n");
    else printf("NO\n");
    for(i=0;i<n;i++)
        printf("%d ",s[i]);
    printf("\n");
}
    return 0;
}
