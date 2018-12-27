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
    int v[maxn];
    int len[maxn];
}E[maxn];

void init()
{
    for(int i = 1; i <= n; i++){
        memset(E[i].v, 0, sizeof(E[i].v));
        memset(E[i].len, 0, sizeof(E[i].len));
        /*E[i].v.clear();
        E[i].len.clear();*/
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
            E[x].v[p] = y;
            E[x].len[p++] = z;
            E[y].v[p] = x;
            E[y].len[p++] = z;
            /*E[x].v.pb(y);
            E[x].len.pb(z);
            E[y].v.pb(x);
            E[y].len.pb(z);*/
        }
        priority_queue<pair<int, int> > Q;
        Q.push(mp(-d1[1], 1));
        while(!Q.empty())
        {
            int now = Q.top().second;
            int len = -Q.top().first;
            Q.pop();
            //int total = E[now].v.size();
            for(int i = 0; i < p; i++)
            {
                int v = E[now].v[i];
                int dist = len + E[now].len[i];
                //printf("dist = %d.\n", dist);
                if(dist < d1[v])
                {
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
        printf("%d\n", d2[n]);
    }
    return 0;
}
