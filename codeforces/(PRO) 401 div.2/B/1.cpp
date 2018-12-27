#include<stdio.h>
#include<algorithm>
#define maxn 1010
using namespace std;

bool cmp(int a, int b)
{
    return a > b;
}
char s[maxn], m[maxn], mm[maxn];
int main()
{
    int n;
    while(~scanf("%d\n", &n))
    {
        int i;
        int minflick = 0, maxflick = 0;
        for(i = 1; i <= n + 1; i++)scanf("%c", s + i);
        s[i] = 0;
        for(i = 1; i <= n + 1; i++)scanf("%c", m + i);
        m[i] = 0;
        sort(s + 1, s + 1 + n);
        sort(m + 1, m + 1 + n);
        for(i = 1; i <= n; i++)
        {
            mm[i] = m[i];
        }
        for(i = n; i >= 1; i--)
        {
            int j;
            for(j = n; j >= 1; j--)
            {
                if(mm[j] >= s[i])
                {
                    minflick++;
                    mm[j] = -1;
                    break;
                }
            }
        }
            minflick = n - minflick;
        for(i = 1; i <= n; i++)
        {
            int j;
            for(j = 1; j <= n ; j++)
            {
                if(m[j] > s[i])
                {
                    m[j] = 0;
                    maxflick++;
                    break;
                }
            }
        }
        printf("%d\n%d\n", minflick, maxflick);
    }
    return 0;
}
