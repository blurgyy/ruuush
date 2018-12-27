#include<stdio.h>
#define ll long long
ll n, m, k;
int check(ll h)
{
    ll sum = 0;
    if(h < k)
    {
        sum += k + (h * h)/2 - h/2;
    }
    if(h == k)
    {
        sum += ((1 + h) * h)/2;
    }
    if(h > k)
    {
        sum += ((h - k + 1 + h) * k)/2;
    }
    if(h < n - k + 1)
    {
        sum += (n - k) + ((1 + h - 2) * (h - 2))/2;
    }
    if(h == n - k + 1)
    {
        sum += ((1 + h) * h)/2 - h;
    }
    if(h > n - k + 1)
    {
        sum += (((h - n + k) + (h - 1)) * (n - k))/2;
    }
    if(sum <= m) return 1;
    else return 0;
}
int main()
{
    ll ans;
    while(~scanf("%I64d%I64d%I64d", &n, &m, &k))
    {
        ll begin = 1, end = m, mid;
        while(begin <= end)
        {
            mid = (begin + end) >> 1;
            if(check(mid))
            {
                ans = mid;
                begin = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
