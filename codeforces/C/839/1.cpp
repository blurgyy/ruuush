#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define maxn 100010
using namespace std;

int n;
vector<int> E[maxn];

double dfs(int u, int prev)
{
    double ans = 0;
    for(int i = 0; i < E[u].size()  ; i++)
        if(E[u][i] != prev)ans += dfs(E[u][i], u) + 1;
    if(ans == 0)return 0;
    if(prev == -1)ans /= E[u].size();
    else ans /= E[u].size()-1;
    return ans;
}

void init()
{
    for(int i = 0; i <= n; i++)E[i].clear();
}

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        int u, v;
        for(int i = 1; i < n; i++)
        {
            scanf("%d%d", &u, &v);
            E[u].push_back(v);
            E[v].push_back(u);
        }
        printf("%.15lf\n", dfs(1, -1));
    }
    return 0;
}

/**

4
1 2
1 3
2 4

5
1 2
1 3
3 4
2 5

*/
