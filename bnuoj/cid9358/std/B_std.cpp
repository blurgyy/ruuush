#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod=1000000007;

ll q_pow(ll a, ll x)
{
    ll res=1;
    while(x)
    {
        if(x&1) res=res*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return res;
}

int t,n;
ll k;
ll A[1010],B[1010];
int main()
{
#ifdef Haha
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
#endif // Haha
    scanf("%d",&t);
    for(int cas=1;cas<=t;cas++)
    {
        assert(scanf("%d",&n)!=EOF);
        assert(scanf("%lld",&k)!=EOF);
        ll res=k;
        A[0]=1;
        for(int i=1;i<n;i++)
        {
            A[i]=A[i-1]*res%mod*q_pow(i,mod-2)%mod;
            res++;
        }
        for(int i=0;i<n;i++)
        {
            assert(scanf("%lld",&B[i])!=EOF);
            for(int j=1;j<=i;j++)
                B[i]=(B[i]-B[i-j]*A[j]%mod+mod)%mod;
            if(i) printf(" ");
            printf("%lld",B[i]);
        }
        printf("\n");
    }
    return 0;
}
