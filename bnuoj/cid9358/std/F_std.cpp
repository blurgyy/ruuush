#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 100010
vector<pair<int,int> > e[N];
set<pair<ll,int> > st;
bool vis[N];
ll a[N];
int n,m;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            e[i].clear();
            a[i]=0;
        }
        while(m--)
        {
            int x,y,c;
            scanf("%d%d%d",&x,&y,&c);
            a[x]+=c;
            a[y]+=c;
            e[x].push_back({y,c});
            e[y].push_back({x,c});
        }
        st.clear();
        for(int i=1;i<=n;++i)
        {
            st.insert({a[i],i});
            vis[i]=false;
        }
        ll ans=0;
        for(int i=1;i<=n;++i)
        {
            int x=st.begin()->second;
            st.erase(st.begin());
            ans=max(ans,a[x]);
            vis[x]=true;
            for(auto &pr:e[x])
            {
                int y=pr.first;
                int c=pr.second;
                if(vis[y]) continue;
                st.erase({a[y],y});
                a[y]-=c;
                st.insert({a[y],y});
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
