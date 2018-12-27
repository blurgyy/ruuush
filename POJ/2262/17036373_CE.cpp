#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

bool check(int x)
{
    int i;
    for(i = 2; i <= sqrt(x); i++)
        if(x % i == 0)return false;
    return true;
}

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        if(n == 0)break;
        int i;
        for(i = 2; i < n; i++)
        {
            if(check(i) && check(n-i))break;
        }
        printf("%d = %d + %d\n", n, i, n-i);
    }
    return 0;
}
