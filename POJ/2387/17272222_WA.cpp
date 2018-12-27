#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define maxn 1010
#define INF 1e9
using namespace std;

int t, n;
int d[maxn];
vector<pair<int, int> > E[maxn];

void init()
{
    for(int i = 0; i < maxn; i++)E[i].clear();
    for(int i = 0; i < maxn; i++)d[i] = INF;
    d[1] = 0;
}

int main()
{
    while(~scanf("%d%d", &t, &n))
    {
        init();
        int x, y, z;
        for(int i = 0; i < n; i++)
        {
            scanf("%d%d%d", &x, &y, &z);
            E[x].push_back(make_pair(y, z));
            E[y].push_back(make_pair(x, z));
        }
        priority_queue<pair<int, int> > Q;
        Q.push(make_pair(-d[1], 1));
        while(!Q.empty())
        {
            int now = Q.top().second;
            Q.pop();
            int total = E[now].size();
            for(int i = 0; i < total; i++)
            {
                int v = E[now][i].first;
                if(d[v] > d[now] + E[now][i].second)
                {
                    d[v] = d[now] + E[now][i].second;
                    Q.push(make_pair(-d[v], v));
                }
            }
        }
        if(d[n] == INF)printf("-1\n");
        else printf("%d\n", d[n]);
    }
    return 0;
}
