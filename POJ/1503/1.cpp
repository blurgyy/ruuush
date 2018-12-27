/**FIALED...
    明天去帝都。。
    心情复杂 我已经好多天没有敲键盘撸码了
    本周开始时
    算了不在这写这些
    这个高精度加法都写不出
    带不带电脑呢
    我是想带的
    对了
    TACHANKA WILL ALWAYS STAND BY YOU.
*/
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define maxn 200
using namespace std;

char n1[maxn], ans[maxn] = {0};

int main()
{
    int j;
    int i = 0;
    char n2[maxn];
    while(1)
    {
        scanf("%s", n1);
        i = 0;
        if(strcmp("0", n1) == 0)break;
        int p1 = strlen(n1) - 1, p2 = strlen(n2) - 1;
        while(p1 >= 0 && p2 >= 0)
        {
            ans[i++] = n1[p1--] - '0' + n2[p2--] - '0';
        }
        while(p1 >= 0)
        {
            ans[i++] = n1[p1--] - '0';
        }
        while(p2 >= 0)
        {
            ans[i++] = n2[p2--] - '0';
        }
        for(j = 0; j < i; j++)
        {
            if(ans[j] >= 10)
            {
                ans[j] -= 10;
                ans[j+1]++;
            }
        }
        strcpy(n2, ans);
    }
    if(ans[j] > 0)i++;
    for(j = i-1; j >= 0; j--)
        printf("%d", ans[j]);
    printf("\n");
    return 0;
}
