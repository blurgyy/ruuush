#include<stdio.h>
int queue[10000000]={0};
int in(int a)
{
    if(a>0&&a<100000)
        return 1;
    else return 0;
}
void print(int line[])
{
    int i;
    for(i=0;i<30;i++)
        printf("%3d",line[i]);
    printf("\n");
}
int main()
{
    int line[100000]={0},vis[100000]={0};
    int f=0,r=1,x;
    int n,k;
    scanf("%d%d",&n,&k);
    queue[0]=n;
    while(line[k]==0)
    {
        x=queue[f];
        vis[x]=1;
        if(in(x-1)&&vis[x-1]==0)
        {
            line[x-1]=line[x]+1;
            queue[r]=x-1;
            r+=1;
            vis[x-1]=-1;
        }
        if(in(x+1)&&vis[x+1]==0)
        {
            line[x+1]=line[x]+1;
            queue[r]=x+1;
            r+=1;
            vis[x+1]=-1;
        }
        if(in(x*2)&&vis[x*2]==0)
        {
            line[x*2]=line[x]+1;
            queue[r]=x*2;
            r+=1;
            vis[x*2]=-1;
        }
        f+=1;
    }
    printf("%d\n",line[k]);
    return 0;
}
