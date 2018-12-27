//是说，我的ret_len函数写的一开始不对。一开始是这样

#include<stdio.h>
#define ll long long

/*

ll ret_len(ll n)
{
    ll len = 1;
    while(n /= 2)
    {
        len *= 2;
    }
    return len - 1;
}
以上是原先写的返回所给数的最终list长度的函数

*/

ll ret_len(ll n)
{
    ll len = 1;
    while(n > 1)
    {
        n /= 2;
        len *= 2;
    }
    return len * 2 - 1;
}

int counter(ll len, ll targ, ll n)
{
    if(n < 2) return n;
    if(targ * 2 == len + 1)return n % 2;
    n /= 2;
    len /= 2;
    if(targ > len + 1)targ -= (len + 1);
    return counter(len, targ, n);
}

int main()
{
    printf("是说，我的ret_len函数写的一开始不对。一开始是这样\n");
    ll n, l, r;
    while(~scanf("%I64d%I64d%I64d", &n, &l, &r))
    {
        ll len = ret_len(n), i;
        int count = 0;
        for(i = l; i <= r; i++) count += counter(len, i, n);
        printf("%d\n", count);
    }
    return 0;
}
// OH SHIT
