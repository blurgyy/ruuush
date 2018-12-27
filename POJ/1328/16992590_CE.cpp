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
    return a.y < b.y;
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
    while(~scanf("%d%d", &n, &d))
    {
        if(n == 0 && d == 0)break;
        int ans = 1;
        d *= d;
        int i;
        int flag = 0;
        int Case = 1;
        cord isl[maxn], cp[maxn];
        for(i = 0; i < n; i++)
        {
            scanf("%lf%lf", &isl[i].x, &isl[i].y);
            double x = isl[i].x;
            double y = isl[i].y;
            if(y > d)
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
            for(j = i+1; j < n; j++)
            {
                if(cp[j].x > cp[i].y)
                {
 