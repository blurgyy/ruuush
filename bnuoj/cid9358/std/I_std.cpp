#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n,k;
char s[1000010];
int main()
{
    scanf("%d",&t);
    for(int cas=1;cas<=t;cas++)
    {
        scanf("%d%d",&n,&k);
        scanf("%s",s);
        assert(strlen(s)==n);
        ll tot=0;
        ll num=0;
        for(int i=0;i<n;i++)
        {
            if(s[i]=='D') num++;
            else tot+=num;
        }
        ll mx=num*(n-num);
        if(k>mx) printf("-1\n");
        else printf("%lld\n",abs(k-tot));
    }
    return 0;
}
