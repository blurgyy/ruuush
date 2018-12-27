#include<stdio.h>
#include<algorithm>
#define maxn 200010
#define sj 1000000010
using namespace std;

struct var
{
    int l;
    int r;
}chess[maxn], prog[maxn];

int main()
{
    int n, m;
    while(~scanf("%d", &n))
    {
        int Min[4] = {sj, sj, sj, sj}, Max[4] = {0};
        int i;
        for(i = 0; i < n; i++)
        {
            scanf("%d%d", &chess[i].l, &chess[i].r);
            Min[0] = min(chess[i].l, Min[0]);
            Max[0] = max(chess[i].l, Max[0]);/**/
            Min[1] = min(chess[i].r, Min[1]);/**/
            Max[1] = max(chess[i].r, Max[1]);
        }
        scanf("%d", &m);
        for(i = 0; i < m; i++)
        {
            scanf("%d%d", &prog[i].l, &prog[i].r);
            Min[2] = min(prog[i].l, Min[2]);
            Max[2] = max(prog[i].l, Max[2]);/**/
            Min[3] = min(prog[i].r, Min[3]);/**/
            Max[3] = max(prog[i].r, Max[3]);
        }
        int ans = 0;
        //printf("Max[2] - Min[1] = %d\nMax[0] - Min[3] = %d\n", Max[2] - Min[1], Max[0] - Min[3]);
        ans = max(ans, Max[2] - Min[1]);
        ans = max(ans, Max[0] - Min[3]);
        printf("%d\n", ans);
    }
    return 0;
}
