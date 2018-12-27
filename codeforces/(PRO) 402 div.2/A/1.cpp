#include<stdio.h>
#include<algorithm>
#define maxn 110
using namespace std;

int abs(int n)
{
    return n > 0 ? n : (-n);
}
int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int a[maxn], b[maxn];
        int i;
        int cnt[6] = {0}, cnt_a[6] = {0}, cnt_b[6] = {0};
        int ans = 0, f = 0;
        for(i = 0; i < n; i++)
        {
            scanf("%d", a + i);
            cnt[a[i]]++;
            cnt_a[a[i]]++;
        }
        for(i = 0; i < n; i++)
        {
            scanf("%d", b + i);
            cnt[b[i]]++;
            cnt_b[b[i]]++;
        }
        for(i = 1; i <= 5; i++)
        {
            if(cnt[i] % 2 == 1)f = 1;
        }
        for(i = 1; i <= 5; i++)
        {
            ans += abs(cnt_a[i] - (cnt[i] / 2));
        }
        if(f) ans = -2;
        printf("%d\n", ans / 2);
    }
    return 0;
}
