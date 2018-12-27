///网上说是LCA...
///dijkstra就过了。。

#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define pb push_back
#define mp make_pair
#define maxn 40010
#define INF 1e9
using namespace std;

int T;
int n, m;
int d[maxn];
vector<pair<int, int> > E[maxn];

void add_edge(int a, int b, int c)
{
    E[a].pb(mp(b, c));
    E[b].pb(mp(a, c));
}

void init()
{
    for(int i = 1; i <= n; i++)E[i].clear();
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        init();
        int a, b, c;
        for(int i = 1; i < n; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, c);
        }
        while(m--)
        {
            scanf("%d%d", &a, &b);
            for(int i = 1; i <= n; i++)d[i] = INF;
            d[a] = 0;
            priority_queue<pair<int, int> > Q;
            Q.push(mp(-d[a], a));
            while(!Q.empty())
            {
                int now = Q.top().second;
                Q.pop();
                int len = E[now].size();
                for(int i = 0; i < len; i++)
                {
                    int v = E[now][i].first;
                    if(d[v] > d[now] + E[now][i].second)
                    {
                        d[v] = d[now] + E[now][i].second;
                        Q.push(mp(-d[v], v));
                    }
                }
            }
            printf("%d\n", d[b]);
        }
    }
}
