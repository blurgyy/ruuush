#include<bits/stdc++.h>
using namespace std;

set<int> rec;

bool check(int x, int base)
{
    int a[50];
    int p = 0;
    while(x)
    {
        a[p++] = x%base;
        x /= base;
    }
    for(int i = 0; i < p/2; i++)
        if(a[i] != a[p-i-1])return false;
    return true;
}

int main()
{
    int s, e, l, r;
    while(~scanf("%d%d%d%d", &s, &e, &l, &r))
    {
        int ans = 0;
        for(int base = l; base <= r; base++)
        {
            rec.clear();
            for(int i = s; i <= e; i++)
            {
                if()
                if(check(i, base))ans += base;
                else ans ++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
