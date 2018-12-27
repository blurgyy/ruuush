#include<stdio.h>
int main()
{
    int n,c,d,f,ff,rating;
    int i;
    while(scanf("%d",&n)!=EOF)
    {
        rating=-1;
        f=0;
        ff=0;
        for(i=0;i<n;i++)
        {
            scanf("%d%d",&c,&d);
            if(d==2)f=1;
            if(c<0)
            {
                if(d==2)rating-=c;
                if(d==1&&rating>=0)rating-=c;
                if(d==1&&rating<0&&i!=n-1)
                    ff=2;
            }
            if(c>0)
            {
                if(d==1)rating+=c;
                if(d==2&&rating<0)rating+=c;
                if(d==2&&rating>=0&&i!=n-1)
                    ff=2;
            }
        }
        if(f==0)printf("Infinity\n");
        else if(ff==2)printf("Impossible\n");
        else if(f==1&&ff==0)printf("%d\n",rating);
    }
    return 0;
}
