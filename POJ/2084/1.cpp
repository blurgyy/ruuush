#include<cstdio>

int n;
int ans[110] = {0};

int f(int n)
{
    int i,r=0;
    if(n==1)return 1;
    else
    {
        for(i=n-1;i>=1;i--)
        r+=f(i)*f(n-i);
        ans[n] = r;
        return r;
    }
}


int main()
{
    ans[0] = 0;
    ans[1] = 1;
    while(scanf("%d",&n)!=EOF)
    {
        if(n==-1)break;
        printf("%d\n",f(n+1));
    }
    return 0;
}
