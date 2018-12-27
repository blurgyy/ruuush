#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int pos1, pos2, m, n, lake;

int exgcd(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int ret = exgcd(b, a%b, x, y);
    int t = x;
    x = y;
    y = t - (a/b) * y;
    return ret;
}

int bs(int left, int right, int x, int y, int gcd)
{
    if(left >= right)return right;
    int mid = (left + right)>>1;
    if(x + mid * (n/gcd) < y - mid * (m/gcd))return bs(mid + 1, right, x, y, gcd);
    return bs(left, mid, x, y, gcd);
}

int main()
{
    while(~scanf("%d%d%d%d%d", &pos1, &pos2, &m, &n, &lake))
    {
        int x, y;
        int dist = pos1 - pos2;
        int gcd = exgcd(m, n, x, y);
        if(dist % gcd)
        {
            printf("Pat\n");
            continue;
        }
        x *= dist / gcd;
        y *= dist / gcd;
        printf("x = %d, y = %d\n", x, y);
        int tmp = bs(0, 100000000, x, y, gcd);
        printf("%d\n", x + tmp * n / gcd);
    }
    return 0;
}
