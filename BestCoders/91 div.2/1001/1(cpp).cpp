#include<stdio.h>
#include<algorithm>
using namespace std;

int val[30], cnt[30];

void sfunc(int left, int right)
{
    int i = left, j = right;
    if(i >= j)return;
    int kv = val[i], kc = cnt[i];
    while(i < j)
    {
        while(i < j && val[j] < kv)j--;
        val[i] = val[j];
        cnt[i] = cnt[j];
        while(i < j && val[i] > kv)i++;
        val[j] = val[i];
        cnt[j] = cnt[i];
    }
    val[i] = kv;
    cnt[i] = kc;
    sfunc(left, i - 1);
    sfunc(i + 1, right);
}

int sum(int n, int l, int r)
{
    return n * (((l + r) * (r - l + 1)) / 2);
}

int main()
{
    int T;
    scanf("%d", &T);
    int res;
    while(T--)
    {
        res = 0;
        int n;
        scanf("%d", &n);
        int i;
        for(i = 1; i <= n; i++)
        {
            scanf("%d%d", val + i, cnt + i);
        }
        sfunc(1, n);
        /*for(i = 1; i <= n; i++)
        {
            printf("val[%d] = %d,\tcnt[%d] = %d\n", i, val[i], i, cnt[i]);
        }*/
        for(i = 1; i <= n; i++)
        {
            int temp = res;
            int j, tag = 1;
            for(j = i, res = 0; j >= 1; j--)
            {
                res += sum(val[j], tag, tag + cnt[j] - 1);
                //printf("i = %d, result = %d.\ntag = %d\n", i, res, tag + cnt[j]);
                tag += cnt[j];
            }
            if(temp > res)
            {
                res = temp;
                break;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
