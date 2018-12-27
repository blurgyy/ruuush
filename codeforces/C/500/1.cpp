#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define maxn 1010
using namespace std;

int n, m;
int ans;
int w[maxn], b[maxn];
int Q[maxn];
int p;
bool vis[maxn];
vector<int> seq;

void inline init()
{
    memset(w, 0, sizeof(w));
    memset(b, 0, sizeof(b));
    seq.clear();
    memset(vis, 0, sizeof(vis));
    ans = 0;
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        init();
        for(int i = 1; i <= n; i++)
            scanf("%d", w + i);
        for(int i = 1; i <= m; i++)
        {
            scanf("%d", b + i);
            if(!vis[i])
            {
                seq.push_back(b[i]);
                vis[i] = true;
            }
        }
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= m; i++)
        {
            for(int j = i-1; j >= 1; j--)
            {
                if(b[j] == b[i])break;
                if(!vis[b[j]])
                {
                    ans += w[b[j]];
                    vis[b[j]] = true;
                }
            }
            memset(vis, 0, sizeof(vis));
        }
        printf("%d\n", ans);
    }
    return 0;
}
