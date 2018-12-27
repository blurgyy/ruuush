#include<bits/stdc++.h>
using namespace std;
char s[10];
int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        bool mm=true;
        for(int i=0;i<n;i++)
        {
            scanf("%s",s);
            if(s[0]!='P')mm=false;
        }
        puts(mm? "MILLION Master":"NAIVE Noob");
    }
    return 0;
}
