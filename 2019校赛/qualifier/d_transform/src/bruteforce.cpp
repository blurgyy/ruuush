#include<bits/stdc++.h>
using namespace std;
int a[100010];
int b[100010];
int check(int n)
{
    for(int i = 1 ; i<=n; i++)
    {
        if(a[i]!=i) return 1;
    }
    return 0;
}
int getnext(int n)
{
    for(int i = 1 ; i<=n; i++)
    {
        a[i]=i;
    }

    list<int> l;
    for(int i = 1 ; i<=n; i++)
    {
        if(i%2) l.push_back(a[i]);
        else l.push_front(a[i]);
    }
    int g=1;
    for(auto i: l)
    {
        a[g]=i;
        g++;
    }
    for(int i=1;i<=n;i++)
    {
        b[a[i]]=i;
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n ;
        scanf("%d",&n);
        getnext(n);
        int ans=1;
        int x=1;
        while(b[x]!=1)
        {
            x=b[x];
            ans++;
        }
       printf("%d\n",ans);
    }
}
