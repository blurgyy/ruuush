/**submit-A*/
#include<cstdio>
#include<algorithm>
using namespace std;

char seq[] = "v<^>";
char f, l;
int n;
int ans;

int main()
{
    while(~scanf("%c %c", &f, &l))
    {
        ans = 0;
        scanf("%d", &n);
        getchar();
        int pf, pl;
        for(int i = 0; i < 4; i++)
        {
            if(f == seq[i])pf = i;
            if(l == seq[i])pl = i;
        }
        int t1 = pf - pl;
        int t2 = pl - pf;
        if(t1 < 0)t1 += 4;
        else if(t2 < 0)t2 += 4;
        if(n % 2 == 0);
        else if(n % 4 == t1)ans = 1;
        else if(n % 4 == t2)ans = -1;
        if(ans == 1)printf("ccw\n");
        else if(ans == -1)printf("cw\n");
        else printf("undefined\n");
    }
    return 0;
}
