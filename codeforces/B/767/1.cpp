#include<stdio.h>
#define maxn 100010
int main()
{
    long long ts, tf, t;
    int n;
    while(~scanf("%I64d%I64d%I64d", &ts, &tf, &t))
    {
        int cnt = 0, sav, ans;
        scanf("%d", &n);
        int i;
        for(i = 0; i < n; i++)
        {
            int temp, temp2;
            scanf("%d", &temp);
            if(i == 0)sav = temp;
            ans = sav;
            if(temp > ts + cnt * t)
            {
                ans = ts + cnt * t;
                printf("%d", ans);
                continue;
            }
            if(temp - temp2 > t)ans = temp2 + t;
            cnt++;
            if(i == n - 1)
            {
                if(ts + cnt * t > tf - t)
                {
                    printf("%d\n", ans);
                }
                else printf("%d\n", ts + cnt * t);
            }
            temp2 = temp;
        }
    }
    return 0;
}
