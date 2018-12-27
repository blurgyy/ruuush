#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 110
using namespace std;

int n, k;
int a[maxn];
int sum, cnt, ans;

int main()
{
    while(~scanf("%d%d", &n, &k))
    {
        sum = 0;
        cnt = 0;
        ans = 0;
        for(int i = 0; i < n; i++)
        {
            scanf("%d", a + i);
            sum += a[i];
            if(sum >= 8)
            {
                sum -= 8;
                cnt += 8;
            }
            else
            {
                cnt += sum;
                sum = 0;
            }
            if(cnt >= k && ans == 0)ans = i+1;
        }
        if(ans)printf("%d\n", ans);
        else printf("-1\n");
    }
    return 0;
}
