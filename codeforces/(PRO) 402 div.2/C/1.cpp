#include<stdio.h>
#include<algorithm>
#define maxn 200010
using namespace std;

int a[maxn], b[maxn], honest[maxn] = {0}, diff[maxn][2];

void quicksort(int left, int right)
{
    if(left >= right) return ;
    int i = left, j = right, key0 = diff[i][0], key1 = diff[i][1];
    while(i < j)
    {
        while(i < j && key1 >= diff[j][1])j--;
        diff[i][0] = diff[j][0];
        diff[i][1] = diff[j][1];
        while(i < j && key1 <= diff[i][1])i++;
        diff[j][0] = diff[i][0];
        diff[j][1] = diff[i][1];
    }
    diff[i][0] = key0;
    diff[i][1] = key1;
    quicksort(left, i - 1);
    quicksort(i + 1, right);
}

int main()
{
    int n, k;
    while(~scanf("%d%d", &n ,&k))
    {
        int i, cnt_honest = 0, ans = 0, tag = 0;
        for(i = 0; i < n; i++)
            scanf("%d", a + i);
        for(i = 0; i < n; i++)
        {
            scanf("%d", b + i);
            if(a[i] < b[i])
            {
                cnt_honest++;
                honest[i] = 1;
                ans += a[i];
            }
            else
            {
                diff[tag][0] = i;//dishonest的商家的编号
                diff[tag++][1] = b[i] - a[i];//后来比之前价格贵了多少
            }
        }
        if(cnt_honest >= k)
        {
            for(i = 0; i < n; i++)
            {
                if(!honest[i])ans += b[i];
            }
        }
        else
        {
            quicksort(0, tag-1);
            k -= cnt_honest;
            for(i = 0; i < tag; i++)
            {

                ans += a[diff[i][0]];
                b[diff[i][0]] = 0;
                k--;
                if(k == 0)break;
            }
            //printf("ans = %d\n", ans);
            for(i = 0; i < n; i++)
            {
                if(!honest[i])ans += b[i];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
