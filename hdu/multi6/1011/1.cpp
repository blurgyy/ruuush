#include<cstdio>
#include<algorithm>
using namespace std;

int T, n;
int a, b, c, ab, bc, ac, abc;

bool check()
{
    if(ab < abc || bc < abc || ac < abc)return false;
    if(a < ab + ac - abc)return false;
    if(b < ab + bc - abc)return false;
    if(c < ac + bc - abc)return false;
    return true;
}

int calc()
{
    return a + b + c - ab - ac - bc + abc;
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        int ans = 0;
        while(n--)
        {
            scanf("%d%d%d%d%d%d%d", &a, &b, &c, &ab, &bc, &ac, &abc);
            if(!check())continue;
            ans = max(ans, calc());
        }
        printf("%d\n", ans);
    }
    return 0;
}
