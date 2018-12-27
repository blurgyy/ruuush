#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1010
using namespace std;

char num[maxn];
int ans;

int main()
{
    while(~scanf("%s", num))
    {
        if(num[0] == '0')break;
        ans = 0;
        while(true)
        {
            int len = strlen(num);
            for(int i = 0; i < len; i++)
                ans += num[i] - '0';
            if(ans < 10)break;
            int p = 0;
            while(ans)
            {
                num[p++] = ans % 10 + '0';
                ans /= 10;
            }
            num[p] = 0;///×¢Òâ×Ö·û´®Ä©Î²ÒªÓÐ'\0'
        }
        printf("%d\n", ans);
    }
    return 0;
}
