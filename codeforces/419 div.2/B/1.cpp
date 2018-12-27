#include<cstdio>
#include<algorithm>
#define maxn 200010
using namespace std;

int n, k, q;
int line[maxn];

int main()
{
    while(~scanf("%d%d%d", &n, &, &q))
    {
        int l, r, ans = 0;
        memset(line, 0, sizeof(line));
        while(n--)
        {
            scanf("%d%d", &l, &r);
            line[l]++;
            line[r]--;
        }
        while(q--)
        {
            scanf("%d%d", &l, &r);
            for(int i = l; i <= r; i++)
            {

            }
        }
    }
}
