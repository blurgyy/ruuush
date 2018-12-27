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
        printf("%lf\t%lf\n", a[i].x, a[i].y);
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
        for(i = n - 1; i >= 0; i--)
        {
            int j;
            int tmp = -1;
            for(j = i - 1; j >= 0; j--)
            {
                if(cp[j].y < cp[i].x)
                {
                    if(tmp == j)break;
                    ans++;
                    i = j + 1;
                    tmp = j;
                    break;
                }
            }
        }
        if(n == 0)ans = 0;
        printf("Case %d: %d\n", Case++, ans);
        out(cp, n);
    }
    return 0;
}


/**

9 84
-44 46
-45 25
-27 30
93 57
-22 45
84 17
74 58
-29 33
24 12
Case 13: 1

*/
