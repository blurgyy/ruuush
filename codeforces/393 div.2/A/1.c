#include<stdio.h>
int main()
{
    int m,d,r;
    while(scanf("%d%d",&m,&d)!=EOF)
    {
        int t;
        if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)t=31;
        else if(m==2)t=28;
        else t=30;
        t-=8-d;
        r=t/7+1;
        if(t%7==0)printf("%d\n",r);
        else printf("%d\n",r+1);
    }
    return 0;
}
