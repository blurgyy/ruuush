#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define maxn 510
#define INF 1e9
using namespace std;

int f, n, m, w;
int d[maxn];
bool ans;
vector<pair<int,int> > E[maxn];

void init()
{
    for(int i = 0; i < maxn; i++)E[i].clear();
    for(int i = 0; i < maxn; i++)d[i] = INF;
    ans = false;
}

int main()
{
    scanf("%d", &f);
    while(f--)
    {
        scanf("%d%d%d", &n, &m, &w);
        init();
        int x, y, z;
        while(m--)
        {
            scanf("%d%d%d", &x, &y, &z);
            E[x].push_back(make_pair(y, z));
            E[y].push_back(make_pair(x, z));
        }
        while(w--)
        {
            scanf("%d%d%d", &x, &y, &z);
            E[x].push_back(make_pair(y, -z));
            ///E[y].push_back(make_pair(x, -z));
        }
        for(int start = 1; start <= n; start++)
        {
            //printf("(2)\n");
            priority_queue<pair<int, int> > Q;
            for(int i = 0; i < maxn; i++)d[i] = INF;
            d[start] = 0;
            Q.push(make_pair(-d[start], start));
            while(!Q.empty())
            {
                //printf("(1)\n");
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
                        if(d[start] < 0)
                        {
                            ans = true;
                            break;
                        }
                    }
                }
                if(ans)break;
            }
            if(ans)break;
        }
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
