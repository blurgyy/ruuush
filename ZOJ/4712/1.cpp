#include<cstdio>
#include<cstring>

int t;
int a, m;
int x, y;

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
    return ret;
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &a, &m);
        int Gcd = exgcd(a, m, x, y);
        if(Gcd != 1)printf("Not Exist\n");
        else
        {
            while(x <= 0)x += m;
            printf("%d\n", x);
        }
    }
    return 0;
}
