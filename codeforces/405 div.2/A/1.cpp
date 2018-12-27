#include<stdio.h>
#include<algorithm>

int Find(int a, int b, int c, int d)
{
    while(b - d)
    {
        if(b < d)b += a;
        else d += c;
    }
    return b;
}

int main()
{
    int a, b, c, d;
    while(~scanf("%d%d%d%d", &a, &b, &c, &d))
    {
        int ans;
        if(b < d)
            if(a <= c)ans = -1;
            else ans = Find(a, b, c, d);
        else if(b > d)
            if(c >= a)ans = -1;
            else ans = Find(a, b, c, d);
        else ans = b;
        printf("%d\n", ans);
    }
    return 0;
}
