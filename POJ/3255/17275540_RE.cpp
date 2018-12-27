#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define maxn 10010
#define INF 1e9
using namespace std;

int n, r;
int d[maxn];
int rec[maxn];
int tmp[maxn];
int p, pt;
vector<pair<int, int> > E[maxn];

void init()
{
    for(int i = 1; i <= n; i++)E[i].clear();
    for(int i = 1; i <= n; i++)d[i] = INF;
    d[1] = 0;
    memset(rec, 0, sizeof(rec));
    memset(tmp, 0, sizeof(tmp));
    tmp[0] = 1;
    rec[0] = 1;
    p = 1;
    pt = 1;
}

int main()
{
    while(~scanf("%d%d", &n, &r))
    {
        init();
        int x, y, z;
        while(r--)
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
            tmp[pt++] = now;
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

        for(int i = 1; i < pt; i++)
        {
            if(tmp[i] != rec[i-1])rec[p++] = tmp[i];
            if(rec[p-1] == n)break;
        }

        for(int k = 1; k < p - 1; k++)
        {
            for(int i = 1; i <= n; i++)d[i] = INF;
            d[1] = 0;
            memset(tmp, 0, sizeof(tmp));
            p = 0;
            priority_queue<pair<int, int> > q;
            q.push(make_pair(-d[1], 1));
            while(!q.empty())
            {
                int now = q.top().second;
                q.pop();
                int total = E[now].size();
                for(int i = 0; i < total; i++)
                {
                    int v = E[now][i].first;
                    if(d[v] > d[now] + E[now][i].second)
                    {
                        //printf("!%d, %d, %d, %d\n", now, v, rec[k], rec[k+1]);
                        if(now == rec[k] && v == rec[k+1])continue;
                        //printf("%d, %d\n", now, v);
                        d[v] = d[now] + E[now][i].second;
                        q.push(make_pair(-d[v], v));
                    }
                }
            }
            tmp[p++] = d[n];
        }
/*
        for(int i = 0; i < p; i++)
            printf("%d ", tmp[i]);
        printf("\n");
*/
        if(d[n] == INF)printf("-1\n");
        else printf("%d\n", d[n]);
    }
    return 0;
}
