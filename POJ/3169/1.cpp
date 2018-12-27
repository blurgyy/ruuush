#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define maxn 1010
using namespace std;
const int INF = 1e9;

int n, ml, md;
vector<pair<int, int> > E[maxn];

void init()
{
    for(int i = 1; i <= n; i++)E[i].clear();
}

int main()
{
    scanf("%d%d%d", &n, &ml, &md);
    init();
    int a, b, c;
    while(ml--)
    {
        scanf("%d%d%d", &a, &b, &c);
        E[a].push_back(make_pair(b, c));
        E[b].push_back(make_pair(a, c));
    }
    while(md--)
    {
        scanf("%d%d", &a, &b, &c);
        int ma = max(a, b);
        int mi = min(a, b);
        E[ma].push_back(make_pair(mi, -c));
        E[mi].push_back(make_pair(ma, INF));
    }

}
