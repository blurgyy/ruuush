#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=100010;

int t,n,m,k;
ll a[N],b[N],c[N];
int main()
{
#ifdef Haha
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
#endif // Haha
    scanf("%d",&t);
    for(int cas=1;cas<=t;cas++)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=0;i<n;i++) scanf("%lld",&a[i]);
        for(int i=0;i<m;i++) scanf("%lld",&b[i]);
        for(int i=0;i<k;i++) scanf("%lld",&c[i]);
        ll ans=1e12;
        int pos1=0,pos2=0;
        for(int i=0;i<m;i++)
        {
            ll dis1=1e12,dis2=1e12;
            while(pos1<n&&a[pos1]<b[i]) pos1++;
            if(pos1) dis1=min(dis1,b[i]-a[pos1-1]);
            if(pos1<n) dis1=min(dis1,a[pos1]-b[i]);
            while(pos2<k&&c[pos2]<b[i]) pos2++;
            if(pos2) dis2=min(dis2,b[i]-c[pos2-1]);
            if(pos2<k) dis2=min(dis2,c[pos2]-b[i]);
            ans=min(ans,dis1+dis2);
        }
        printf("%lld\n",ans+3);
    }
    return 0;
}
