#include<cstdio>
#include<vector>
#include<cstring>
#define maxn 200010
#define ll long long
using namespace std;

int T, n, m;
int a[maxn];
int sq[maxn] = {0};
vector<int> num[maxn];

int main()
{
    int t = 1, p = 1;
    while(t < 400000)
    {
        for(; p <= t && p < maxn; p++)
            sq[p] = t;
        t <<= 1;
    }
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", a + i);
            num[i].push_back(a[i]);
        }
        for(int i = 2; i <= n; i++)
        {
            int len = m % sq[i];
            for(int j = 0; j < len; j++)
                num[i].push_back(a[i] = a[i] ^ num[i-1][j]);
        }
        for(int i = 1; i <= n; i++)
            printf("%d ", a[i]);
        printf("\n");
        for(int i = 0; i < n; i++)
            num[i].clear();
    }
    return 0;
}
