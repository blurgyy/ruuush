#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define maxn 1010
#define mp make_pair
#define pb push_back
using namespace std;
const int INF = 1e9;

int c, r;
int d[maxn];
int s, t, limit;
priority_queue<pair<int, pair<int, int> > > E[maxn];

void add_edge(int from, int to, int height, int cost)
{
    E[from].push(mp(height, mp(to, cost)));
    E[to].push(mp(height, mp(from, cost)));
}

void init()
{
    for(int i = 0; i < maxn; i++)
        while(!E[i].empty())E[i].pop();
    for(int i = 0; i < maxn; i++)d[i] = INF;
}

int main()
{
    priority_queue<pair<int, int> > Q;
    while(~scanf("%d%d", &c, &r))
    {
        int from, to, height, cost;
        for(int i = 0; i < r; i++)
        {
            scanf("%d%d%d%d", &from, &to, &height, &cost);
            add_edge(from, to, height, cost);
        }
        scanf("%d%d%d", &s, &t, &limit);
        d[s] = 0;
        Q.push(mp(-d[s], s));
        while(!Q.empty())
        {
            int now = Q.top()
        }
    }
    return 0;
}
