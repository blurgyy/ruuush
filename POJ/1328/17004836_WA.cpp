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
            /*if(cp[i].y < cp[i+1].x)
            {
                ans++;
                i++;
            }*/
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
        printf("Case %d: %d\n", Case++, ans);
        //out(cp, n);
    }
    return 0;
}


/**

29 56
-75 5
24 48
-10 16
-90 19
56 47
53 20
-66 1
40 48
11 56
-25 13
88 8
49 2
91 8
70 27
61 24
-67 45
-24 36
-27 31
-51 47
58 40
-74 16
-46 32
-70 3
-4 16
2 44
82 45
-66 15
66 26
79 47
Case 61: 4

*/
