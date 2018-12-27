#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans;
int n,k,tot;
int a[100010];
bool rev;
void dfs(int x,int now,int sum)
{
    if(now==k)
    {
        if(rev) ans^=1LL*(tot-sum)*(tot-sum);
        else ans^=1LL*sum*sum;
        return;
    }
    if(n-x<k-now) return;
    dfs(x+1,now,sum);
    dfs(x+1,now+1,sum+a[x]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        tot=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d",a+i);
            tot+=a[i];
        }
        ans=0;
        rev=0;
        if(k>n/2)
        {
            rev=true;
            k=n-k;
        }
        dfs(0,0,0);
        printf("%lld\n",ans);
    }
    return 0;
}
