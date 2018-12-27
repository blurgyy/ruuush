#include<stdio.h>
#include<algorithm>
#define ll long long
#define maxn 100010
using namespace std;
ll n;
int l, r, s[maxn], tag;
void split(ll x)
{
    int i;
    if(x == 1 || x == 0)
    {
        s[tag++] = x;
        return;
    }
    else if(x == 2)
    {
        s[tag++] = 1;
        s[tag++] = 0;
        s[tag++] = 1;
    }
    else if(x == 3)
    {
        s[tag++] = 1;
        s[tag++] = 1;
        s[tag++] = 1;
    }
    else
    {
        split(x / 2);
        split(x % 2);
        split(x / 2);
    }
}
int main()
{
    while(~scanf("%I64d%d%d", &n, &l, &r))
    {
        int count = 0;
        tag = 1;
        split(n);
        int i;
        for(i = l; i <= r; i++)
        {
            count += s[i];
        }
        printf("%d\n", count);
    }
    return 0;
}
