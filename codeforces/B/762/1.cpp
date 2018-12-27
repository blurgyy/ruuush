#include<stdio.h>
#include<string.h>
#include<algorithm>
#define maxn 300010
using namespace std;
int vu[maxn], vs[maxn];
int main()
{
    char u[] = "USB", s[] = "PS/2";
    int a, b, c;
    while(~scanf("%d%d%d", &a, &b, &c))
    {
        int m;
        scanf("%d", &m);
        int i, p1, p2;
        for(i = 1, p1 = 1, p2 = 1; i <= m; i++)
        {
            int temp;
            char t[10];
            scanf("%d %s", &temp, t);
            if(strlen(t) == 4)t[3] = 0;
            else t[4] = 0;
            if(t == u)vu[p1++] = temp;
            else vs[p2++] = temp;
        }
        sort(vu + 1, vu + 1 + m);
        sort(vs + 1, vs + 1 + m);
        int ans = 0,cnt = 0;
        for(i = 1; i <= a; i++)
        {
            ans += vu[i];
            cnt++;
        }
        for(i = 1; i <= b; i++)
        {
            ans += vs[i];
            cnt++;
        }
        int j;
        for(i = a + 1, j = b + 1; i <= m || j <= m;)
        {
            if(i <= m && vu[i] <= vs[j]) ans += vu[i++];
            else if(j <= m && vu[i] >= vs[j])ans += vs[j++];
            cnt++;
            if(cnt == c + a + b)break;
        }
        printf("%d %d\n", cnt, ans);
    }
}
