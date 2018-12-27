#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
#define pb push_back
#define mp make_pair
#define LL long long
#define max3(x, y, z) max((x), max((y), (z)))
#define min3(x, y, z) min((x), min((y), (z)))
using namespace std;

const LL N = 100010;

struct Edge
{
    vector<LL> v;
    vector<LL> w;
};

Edge edges[N];

int main()
{
    LL n, m;
    LL dis1[N];
    LL dis2[N];
    LL ncase;

    scanf("%lld", &ncase);
    while(ncase --){
        scanf("%lld%lld", &n, &m);
        for(LL i = 1; i <= n; i ++){
            edges[i].v.resize(0);
            edges[i].w.resize(0);
        }
        for(LL i = 0; i < m; i ++){
            LL u, v, w;
            scanf("%lld%lld%lld", &u, &v, &w);
            edges[u].v.pb(v);
            edges[u].w.pb(w);
            edges[v].v.pb(u);
            edges[v].w.pb(w);
        }
        for(LL i = 1; i <= n; i ++){
            dis1[i] = 0x3f3f3f3f;
            dis2[i] = 0x3f3f3f3f;
        }
        dis1[1] = 0;
        priority_queue< pair<LL, LL> > Q;
        Q.push(mp(-dis1[1], 1));
        while(!Q.empty()){
            LL u = Q.top().second;
            LL w = -Q.top().first;
            Q.pop();
            for(LL i = 0; i < edges[u].v.size(); i ++){
                LL v = edges[u].v[i];
                LL t = w + edges[u].w[i];

                //printf("%d %d\n", v, t);
                if(t <= dis1[v]){
                    dis2[v] = dis1[v];
                    dis1[v] = t;
                    Q.push(mp(-dis1[v], v));
                }
                if(t < dis2[v] && t > dis1[v]){
                    dis2[v] = t;
                    Q.push(mp(-dis2[v], v));
                }
            }
        }
        //printf("%d\n", dis1[n]);
        printf("%lld\n", dis2[n]);
    }

    return 0;
}
