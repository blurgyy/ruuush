/*
POJ 3295
构造法
p,q,r,s,t枚举所有可能取值
用一个堆栈从字符串末尾进行操作

AC  G++  684K  0MS
*/

#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
const int MAXN=120;
int sta[MAXN];//数组实现堆栈
char str[MAXN];
int p,q,r,s,t;
void  DoIt()
{
    int top=0;
    int len=strlen(str);
    for(int i=len-1;i>=0;i--)
    {
        if(str[i]=='p') sta[top++]=p;
        else if(str[i]=='q') sta[top++]=q;
        else if(str[i]=='r') sta[top++]=r;
        else if(str[i]=='s') sta[top++]=s;
        else if(str[i]=='t') sta[top++]=t;
        else if(str[i]=='K')
        {
            int t1=sta[--top];
            int t2=sta[--top];
            sta[top++]=(t1&&t2);
        }
        else if(str[i]=='A')
        {
            int t1=sta[--top];
            int t2=sta[--top];
            sta[top++]=(t1||t2);
        }
        else if(str[i]=='N')
        {
            int t1=sta[--top];
            sta[top++]=(!t1);
        }
        else if(str[i]=='C')
        {
            int t1=sta[--top];
            int t2=sta[--top];
            if(t1==1&&t2==0)sta[top++]=0;
            else sta[top++]=1;
        }
        else if(str[i]=='E')
        {
            int t1=sta[--top];
            int t2=sta[--top];
            if((t1==1&&t2==1)||(t1==0&&t2==0)) sta[top++]=1;
            else sta[top++]=0;
        }
    }
}
bool solve()
{
    for(p=0;p<2;p++)
      for(q=0;q<2;q++)
        for(r=0;r<2;r++)
           for(s=0;s<2;s++)
              for(t=0;t<2;t++)
              {
                  DoIt();
                  if(sta[0]==0)return false;
              }
    return true;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%s",&str))
    {
        if(strcmp(str,"0")==0)break;
        if(solve())printf("tautology\n");
        else printf("not\n");
    }
    return 0;
}
