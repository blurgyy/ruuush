#include<stdio.h>
int main()
{
    int a,b;
    while(scanf("%d%d",&a,&b)!=EOF)
    {
        if(b==0 && a==0)printf("NO\n");
        else if(a-b>=-1&&a-b<=1)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
