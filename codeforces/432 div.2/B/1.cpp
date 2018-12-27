#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;
const ll infinity = 0x7fffffffffffffff;

ll dis1, dis2;
ll ax, ay;
ll bx, by;
ll cx, cy;

ll sq(ll x)
{
    return x * x;
}

int main()
{
    while(~scanf("%I64d%I64d%I64d%I64d%I64d%I64d", &ax, &ay, &bx, &by, &cx, &cy))
    {
        if(bx - ax == cx - bx && by - ay == cy - by)
        {
            printf("No\n");
            continue;
        }
        dis1 = sq(ax - bx) + sq(ay - by);
        dis2 = sq(bx - cx) + sq(by - cy);
        //printf("dis1 = %lld, dis2 = %lld\n", dis1, dis2);
        if(dis1 == dis2)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

/**

0 1 1 1 1 0
1 1 0 0 1000 1000
1 1 2 2 3 3

*/
