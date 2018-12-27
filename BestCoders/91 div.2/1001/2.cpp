#include<stdio.h>
#include<algorithm>
#define ll long long
using namespace std;

pair<int, int>p[30];

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n;
        scanf("%d", &n);
        int i;
        for(i = 1; i <= n; i ++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            make_pair(a,b);
        }
        sort(p, p + n);
        for(i = n; i >= 1; i--)
        {
            int j;
            for(j = )
        }
    }
}
