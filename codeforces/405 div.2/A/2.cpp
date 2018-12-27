#include<stdio.h>

int Find(int t1, int a, int t2, int b)
{
    while(a - b)
    {
        if(a < b)a += t1;
        else b += t2;
        if(a < 0 || b < 0)break;
    }
    return a;
}
int main()
{
    int t1, r, t2, m;
    while(~scanf("%d%d%d%d", &t1, &r, &t2, &m))
    {
        int ans;
        if(r % 2 != m % 2 && t1 % 2 == t2 % 2 && t1 % 2 == 0)ans = -1;
        else if(r % 10 != m % 10 && t1 % 5 == 0 && t2 % 5 == 0)ans = -1;
        else ans = Find(t1, r, t2, m);
        printf("%d\n", ans);
    }
    return 0;
}
