#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define maxn 510
#define INF 1e9
using namespace std;

int f, n, m, w;
int d[maxn], cnt[maxn];
bool inq[maxn];
vector<pair<int,int> > E[maxn];

void init()
{
    memset(inq, false, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < maxn; i++){
        d[i] = INF;
        E[i].clear();
    }
}

bool check()
{
    for(int i = 1; i <= n; i++)
        if(cnt[i] == n)return true;
    return false;
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
        }
        queue<int> Q;
        Q.push(1);
        d[1] = 0;
        inq[1] = true;
        cnt[1]++;
        while(!Q.empty())
        {
            int now = Q.front();
            Q.pop();
            inq[now] = false;
            int total = E[now].size();
            for(int i = 0; i < total; i++)
            {
                int v = E[now][i].first;
                if(d[v] > d[now] + E[now][i].second)
                {
                    d[v] = d[now] + E[now][i].second;
                    if(inq[v])continue;
                    Q.push(v);
                    inq[v] = true;
                    cnt[v]++;
                }
            }
            if(check())break;
        }
        if(check())printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
