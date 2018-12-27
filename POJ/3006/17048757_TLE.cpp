#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

bool check(int n)
{
    if(n == 1)return false;
    for(int i = 2; i <= n/2; i++)
        if(n % i == 0)return false;
    return true;
}

int main()
{
    int a, d, n;
    while(~scanf("%d%d%d", &a, &d, &n))
    {
        if(!n && a == d && d == n)break;
        int cnt = 0;
        int ans = 0;
        for(int i = a; ; i += d)
        {
            cnt += check(i);
            if(cnt == n)
            {
                ans = i;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
