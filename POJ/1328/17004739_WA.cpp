///我要睡了:(
                ///大致思路通过Bing和别人的博客了解了
                ///好烦没做出来
                ///明天再看
                ///(今天可能)
#include<cstdio>
#include<cmath>
#include<algorithm>
#define maxn 1010
using namespace std;

struct cord
{
    double x;
    double y;
};

bool operator < (cord a, cord b)
{
    if(a.x < b.x)return true;
    if(a.x > b.x)return false;
    return a.y > b.y;
}

void out(cord a[], int n)
{
    int i;
    for(i = 0; i < n; i++)
        printf("%lf %lf\n", a[i].x, a[i].y);
    printf("\n");
}

int main()
{
    int n, d;
    int Case = 1;
    while(~scanf("%d%d", &n, &d))
    {
        if(n == 0 && d == 0)break;
        int ans = 1;
        d *= d;
        int i;
        int flag = 0;
        cord isl[maxn], cp[maxn];
        for(i = 0; i < n; i++)
        {
            scanf("%lf%lf", &isl[i].x, &isl[i].y);
            double x = isl[i].x;
            double y = isl[i].y;
            if(y*y > d)
            {
                flag = 1;
                continue;
            }
            cp[i].x = x - sqrt(d - y*y);
            cp[i].y = x + sqrt(d - y*y);
        }
        if(flag)
        {
            printf("Case %d: -1\n", Case++);
            continue;
        }
        sort(cp, cp + n);
        for(i = 0; i < n; i++)
        {
            int j;
            int tmp;
            //if(cp[i].y < cp[i+1].x)i++;
            for(j = i+1; j < n; j++)
            {
                if(cp[j].x > cp[i].y)
                {
                    if(tmp == j)break;
                    ans++;
                    i = j - 1;
                    //printf("i = %d, j = %d\n", i, j);
                    tmp = j;
                    break;
                }
            }
        }
        if(n == 0)ans = 0;
        for(i = 0; i < n; i++)
            if(cp[i].x == cp[i].y)ans++;
        printf("Case %d: %d\n", Case++, ans);
        //out(cp, n);
    }
    return 0;
}


/**

12 58
-72 24
-86 51
81 25
14 32
-74 38
30 4
40 8
-39 58
-37 36
-31 13
-28 25
27 45

*/
