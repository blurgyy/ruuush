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
vector<pair<int, int> > E[maxn];

void init()
{
    for(int i = 1; i <= n; i++){
        E[i].clear();
        d1[i] = INF;
        d2[i] = INF;
    }
    d1[1] = 0;
}

int T;

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &r);
        init();
        int x, y, z;
        while(r--)
        {
            scanf("%d%d%d", &x, &y, &z);
            E[x].pb(mp(y, z));
            E[y].pb(mp(x, z));
        }
        priority_queue<pair<int, int> > Q;
        Q.push(mp(-d1[1], 1));
        while(!Q.empty())
        {
            int now = Q.top().second;
            int len = -Q.top().first;
            Q.pop();
            int total = E[now].size();
            for(int i = 0; i < total; i++)
            {
                int v = E[now][i].first;
                int dist = len + E[now][i].second;
                //printf("dist = %d.\n", dist);
                if(dist <= d1[v])
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
        printf("%d\n", d2[n]);
    }
    return 0;
}
/**

100
4 4
1 2 1
2 4 3
1 3 1
3 4 3

3 3
1 2 1
1 3 2
2 3 1

3 2
1 2 1
2 3 1

*/
