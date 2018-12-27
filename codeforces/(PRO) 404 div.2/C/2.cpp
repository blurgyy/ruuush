//表示
//一定要做出一道题才能平复刚刚打游戏失败的心情
#include<cstdio>
#include<algorithm>
#define ll long long

int main()
{
    ll n, m;
    while(~scanf("%d%d", &n, &m))
    {
        int l, r;
        int mid;
        while(l < r)
        {
            mid = (l + r) / 2;
            if((1 + mid) * mid / 2 < n)l = mid;
            else r = mid;
        }

    }
    return 0;
}
