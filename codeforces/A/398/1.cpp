#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define maxn 100010
#define INF -1e18
using namespace std;

int a, b;
ll ans;

int main()
{
    while(~scanf("%d%d", &a, &b))
    {
        ans = INF;
        if(a == 0)
        {
            ans = -1LL * b * b;
            printf("%I64d\n", ans);
            for(int i = 0; i < b; i++)
                printf("x");
            printf("\n");
            //continue;
            return 0;
        }
        ll part, ret;
        for(part = 1; part <= a; part++)
        {
            ll tmp = (a-part+1) * (a-part+1) + part - 1;
            ll num = b / (part+1);
            tmp -= (num+1) * (num+1) * (b%(part+1)) + num * num * (part + 1 - b % (part+1));
            if(tmp < ans)continue;
            ans = tmp;
            ret = part;
        }
        part = ret;
        printf("%I64d\n", ans);

        int num = b / (part + 1);
        int t = b % (part + 1);
        if(t)
        {
            for(int i = 0; i < num+1; i++)
                printf("x");
            for(int i = 0; i < a - part + 1; i++)
                printf("o");
            t--;
            while(t--)
            {
                for(int i = 0; i < num+1; i++)
                    printf("x");
                printf("o");
            }
            t = part + 1 - b % (part + 1);
            while(t--)
            {
                for(int i = 0; i < num; i++)
                    printf("x");
                if(t)printf("o");
            }
            printf("\n");
        }
        else
        {
            t = part + 1 - b % (part + 1);
            for(int i = 0; i < num; i++)
                printf("x");
            for(int i = 0; i < a - part + 1; i++)
                printf("o");
            t--;
            while(t--)
            {
                for(int i = 0; i < num; i++)
                    printf("x");
                if(t)printf("o");
            }
            printf("\n");
        }
    }
    return 0;
}

/**

28691 28312
98751 29491
1454 26690 -444804

*/
