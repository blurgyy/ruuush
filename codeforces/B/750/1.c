#include<stdio.h>
int main()
{
    int n,dir,temp,f;
    char c[10];
    while(scanf("%d",&n)!=EOF)
    {
        dir=0;
        f=1;
        while(n--)
        {
            scanf("%d %s",&temp,c);
            if((c[0]=='S'||c[0]=='N')&&temp>20000)f=0;
            else if((c[0]=='E'||c[0]=='W')&&(dir==0||dir==20000))f=0;
            else if(c[0]=='S')
            {
                dir+=temp;
                if(dir>20000)f=0;
            }
            else if(c[0]=='N')
            {
                dir-=temp;
                if(dir<0)f=0;
            }
        }
        if(f==0||dir!=0)printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
