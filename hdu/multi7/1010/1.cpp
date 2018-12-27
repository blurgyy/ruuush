#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 200010
#define ll long long
using namespace std;

int T, n, m;
int Case = 1;
int a[maxn];
ll b[maxn];

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        Case = 1;
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++)
            scanf("%d", a + i);
        while(m--)
        {
            printf("%d:\t", Case++);
            for(int i = 1; i < n; i++)
                a[i] = a[i]^a[i-1];
            for(int i = 0; i < n; i++)
            {
                char s[10];
                itoa(a[i], s, 2);
                printf("%08s\t", s);
            }
            printf("\n");
        }
    }
    return 0;
}
