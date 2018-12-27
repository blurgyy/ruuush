#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 110
using namespace std;

int n, k;
int a[maxn];
int sum, row;

bool check(int x)
{
    if(x == 2 || x == 6 || x == 8)return false;
    return true;
}

int main()
{
    while(~scanf("%d%d", &n, &k))
    {
        sum = 0;
        row = 0;
        bool ans = true;
        for(int i = 0; i < k; i++)
        {
            scanf("%d", a + i);
            sum += a[i];
            row += sum/8;
            sum = sum - (sum/8)*8;
            if(check(sum))sum++;
            if(row > n)ans = false;
            if(row == n && sum != 0)ans = false;
        }
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/**

2 2
5 8

1 2
7 1

1 2
4 4

1 4
2 2 1 2

*/
