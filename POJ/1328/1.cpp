#include<cstdio>
#include<math.h>
#include<algorithm>
#define maxn 1010
using namespace std;

struct cord
{
    int x;
    int y;
};

bool operator < (cord a, cord b)
{
    return a.x < b.x;
}

bool cmp(cord a, cord b)
{
    return a.y < b.y;
}

bool in_range(cord arr[], double nx, int i, int dist)
{
    double x = arr[i].x;
    double y = arr[i].y;
    double d = (x - nx)*(x - nx) + y*y;
    if(d < dist)return true;
    return false;
}

bool check(cord arr[], double nx, int start, int end, int dist)
{
    int i;
    for(i = start; i < end; i++)
        if(!in_range(arr, nx, i, dist))return false;
    return true;
}

int main()
{
    int n, d;
    int Case = 1;
    while(scanf("%d%d", &n, &d))
    {
        int ans = 0;
        d *= d;
        if(n == 0 && d == 0)break;
        cord in[maxn];
        int dist[maxn] = {0};
        int i;
        for(i = 0; i < n; i++)
        {
            scanf("%d%d", &in[i].x, &in[i].y);
        }
        sort(in, in + n, cmp);
        if(in[n-1].y > d)
        {
            printf("Case %d: -1\n", Case++);
            continue;
        }
        sort(in, in + n);
        int start = 0;
        for(i = 1; i < n; i++)
        {
            double x = in[i].x;
            double y = in[i].y;
            double nx = x - sqrt(d - y*y);
            if(!check(in, nx, start, i, d))
            {
                printf("\nnx = %lf\nans = %d\nstart = %d\n", nx, ans, start);
                ans++;
                start = i + 1;
                i++;
            }
        }
        if(ans == 0)ans++;
        if(n == 0)ans = 0;
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}
/*

3 2
0 1
-100 1
100 1
*/
