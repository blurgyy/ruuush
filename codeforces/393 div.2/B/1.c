#include<stdio.h>
int main()
{
    int n,m,k;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF)
    {
        m-=n;
        int p=1,t=n-k,f=0;
        int i,j,temp=0;
        for(i=0;2*i+1<n;i++)
        {
            if(k>=i&&n-k>=i&&m>0)
            {
                p++;
                m-=2*i+1;
            }
            if(((2*(i+1)+1)<n)&&m<2*(i+1)+1)
            {
                f=1;
                break;
            }
        }
        if(f==0)
        {
            if(m==n-1&&m!=0)p++;
            else if(m<2*(i+1)+1)f=1;
            else for(j=0;;j++)
            {
                p++;

                if(temp==0)m-=2*i+1+j;
                else m-=temp;
                if(2*i+1+j==n)temp=2*i+1+j;
                if(m<temp)
                {
                    f=1;
                    break;
                }
            }
        }
        printf("%d\n",p);
    }
    return 0;
}
