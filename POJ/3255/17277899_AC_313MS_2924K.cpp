#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define maxn 5010
#define INF 1e9
#define pb push_back
#define mp make_pair
using namespace std;

int n, r;
int d1[maxn], d2[maxn];
int p;
struct edge
{
    vector<int> v;
    vector<int> len;
}E[maxn];

void init()
{
    for(int i = 1; i <= n; i++){
        E[i].v.clear();
        E[i].len.clear();
        d1[i] = INF;
        d2[i] = INF;
    }
    d1[1] = 0;
    p = 0;
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
            E[x].v.pb(y);
            E[x].len.pb(z);
            E[y].v.pb(x);
            E[y].len.pb(z);
        }
        priority_queue<pair<int, int> > Q;
        Q.push(mp(-d1[1], 1));
        while(!Q.empty())
        {
            int now = Q.top().second;
            int len = -Q.top().first;
            Q.pop();
            for(int i = 0; i < E[now].v.size(); i++)
            {
                int v = E[now].v[i];
                int dist = len + E[now].len[i];
                //printf("v = %d, dist = %d.\n", v, dist);
                if(dist < d1[v])
                {
                    d2[v] = d1[v];
                    d1[v] = dist;
                    Q.push(mp(-d1[v], v));
                }
                if(dist > d1[v] && dist < d2[v])
                {
                    d2[v] = dist;
                    Q.push(mp(-d2[v], v));
                }
            }
        }
        /*
        for(int i = 1; i <= n; i++)
            printf("%5d", d1[i]);
        printf("\n");
        for(int i = 1; i <= n; i++)
            printf("%5d", d2[i]);
        printf("\n");
        */
        printf("%d\n", d2[n]);
    }
    return 0;
}
