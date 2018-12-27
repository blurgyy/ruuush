#include<stdio.h>
#include<math.h>
#define maxn 100010
int main()
{
    int k;
    long long n;
    while(~scanf("%I64d%d", &n, &k))
    {
        long long i, cnt = 0, j = 1, v[maxn], vv[maxn];
        for(i = 1; i <= (int)sqrt((double)n); i++)
        {
            if(n % i == 0)
            {
                v[j] = i;
                vv[j++] = n / i;
                cnt++;
            }
        }
        if(v[j-1] == vv[j-1])cnt = cnt * 2 - 1;
        else cnt *= 2;
        if(k <= j - 1)printf("%d\n", v[k]);
        else if(k > cnt)printf("-1\n");
        else printf("%I64d\n", vv[cnt-k+1]);
    }
    return 0;
}
