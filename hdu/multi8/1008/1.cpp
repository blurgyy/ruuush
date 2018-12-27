#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1010
using namespace std;

int T;
int n, k;
struct node
{
    int num;
    char symb[5];
}a[maxn];
char ans[2][5] = {"no\n", "yes\n"};

bool operator < (node a, node b)
{
    return a.num < b.num;
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; i++)
            scanf("%d", &a[i].num);
        for(int i = 0; i < n; i++)
            scanf("%s", a[i].symb);
        int cnt = 0, p = n-1;
        while(cnt != k && p >= 0)
        {
            if(cnt < k)
            {
                while(!strcmp(a[p--].symb, "D") && p >= 0);
                cnt += a[p+1].num;
            }
            else
            {
                while(!strcmp(a[p--].symb, "L") && p >= 0);
                cnt -= a[p+1].num;
            }
        }
        printf("%s", ans[cnt==k]);
    }
    return 0;
}
