#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int t;
int n, b;

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
    y = t - a/b * y;
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        int x, y;
        scanf("%d%d", &n, &b);
        int ans = exgcd(b, 9973, x, y);
        x *= n;
        x = (x%9973 + 9973) % 9973;
        printf("%d\n", x);
    }
    return 0;
}
