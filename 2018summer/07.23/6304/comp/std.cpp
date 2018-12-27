#include<stdio.h>
#include<iostream>
using namespace std;
#define mod 1000000007
typedef long long ll;
ll a[105],f[105];
int main()
{
	//freopen("in.in", "r", stdin);
	//freopen("std.out", "w", stdout);
    ll T;
    scanf("%lld",&T);
    a[0]=f[0]=1;
    for(ll i=1;i<=62;i++)a[i]=a[i-1]*2+1,f[i]=f[i-1]*2;
    ll inv=(mod+1)/2;
    while(T--)
    {
        ll pos=0,n,m,ma=-1,ans=0;
        scanf("%lld",&n);
        m=n;
        for(ll i=62;i>=0;i--)
            if(m-a[i]>=0)
                m-=a[i],pos=pos+(1ll<<i);
        pos+=(m>0);
        ll now=pos-1,num=0;
        for(ll i=1;f[i-1]<=now;i++)
        {
            ll s=f[i-1],step=(now-s)/f[i]+1,e=(step-1)*f[i]+s;
            ll haha=(s+e)%mod*(step%mod)%mod*inv%mod;
            ans=(ans+haha*i%mod)%mod;
            num+=step*i;
        }
        ans=(ans+1+(n-num-1)%mod*(pos%mod)%mod)%mod;
        printf("%lld\n",ans);
    }
}