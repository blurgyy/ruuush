#include<cstdio>
#include<cstring>
#define maxn 1000010
#include<algorithm>
using namespace std;

int n, k;
bool vis[maxn] = {false};

struct Path
{
    int cur;
    int time;
}path[maxn];

int main()
{
    while(~scanf("%d%d", &n, &k))
    {
        int p0 = 0, p = 1;
        int ans = 0;
        memset(vis, 0, sizeof(vis));
        vis[n] = true;
        path[0].cur = n;
        path[0].time = 0;
        if(n == k);
        else if(n > k)
        {
            ans = n - k;
        }
        else while(p0 < p)
        {
            if(path[p0].cur + 1 == k || path[p0].cur - 1 == k || path[p0].cur * 2 == k)
            {
                ans = path[p0].time + 1;
                break;
            }
            if(!vis[path[p0].cur + 1])
            {
                vis[path[p0].cur + 1] = true;
                path[p].cur = path[p0].cur + 1;
                path[p++].time = path[p0].time + 1;
            }
            if(path[p0].cur - 1 > 0 && !vis[path[p0].cur - 1])
            {
                vis[path[p0].cur - 1] = true;
                path[p].cur = path[p0].cur - 1;
                path[p++].time = path[p0].time + 1;
            }
            if(!vis[path[p0].cur * 2] && /**/path[p0].cur * 2 <= 100000/**/)
            {
                vis[path[p0].cur * 2] = true;
                path[p].cur = path[p0].cur * 2;
                path[p++].time = path[p0].time + 1;
            }
            p0++;
            //printf("p0 = %d, p = %d\n", p0, p);
        }
        printf("%d\n", ans);
    }
}