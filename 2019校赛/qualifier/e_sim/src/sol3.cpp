#include<bits/stdc++.h>
using namespace std;
char  a[1000100];
vector<long long> s;
int main()
{
    int t;
    scanf("%d",&t);
    long long  ma= (1ll<<31)-1,num;
    while(t--)
    {
        scanf("%s",a);
        char x[2];
        scanf("%s",x);
        int g=0;
        int k = strlen(a);
        s.clear();
        int flag=0;
        num=-1;
        for(int i = 0 ;i<k;i++)
        {
            if(isdigit(a[i]))
                {
                    if(num==-1) num=0;
                    num= num*10 + a[i]-'0';
                    if(num==0&&isdigit(a[i+1]) ||num>ma) {
                            flag = 1;
                            break;
                    }
                }
            else
            {
                if(a[i]==x[0]) {
                    if(num!=-1)s.push_back(num);
                    num=-1;
                }
                else
                {
                    flag = 1;
                    break;
                }
            }
        }
        if(num!=-1) s.push_back(num);
        if(flag) printf("bad dongdongqiang\n");
        else
        {
            printf("%d\n",s.size());
            for(int i=0;i<s.size();i++)
                printf("%lld\n",s[i]);

        }
    }
}