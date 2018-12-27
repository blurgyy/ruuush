#include<cstdio>
#include<algorithm>
#include<cmath>
#define maxn 2000000
using namespace std;

bool check(int n)
{
    if(n == 1 || n == 2)return false;
    if(n % 2 == 0)return false;
    for(int i = 3; i*i <= n; i++)
        if(n % i == 0)return false;
    return true;
}

int prime[maxn] = {0}, p = 0;

int main()
{
    /*for(int i = 0; i < 1000000; i++)
        if(check(i))prime[p++] = i;
    printf("preprocessing done\n");
    return 0;*/

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
