#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

char n[20] = {0};

int check_zero(int pos)
{
    int i;
    for(i = pos; i < strlen(n); i++)
    {
        if(n[i] == '0')continue;
        return 0;
    }
    return 1;
}

int main()
{
    int k;

    while(~scanf("%s%d", n, &k))
    {
        int len = strlen(n);
        int i, cnt = 0, ans = 0, mark;
        for(i = len-1; i >= 0; i--)
        {
            if(n[i] == '0')cnt++;
        }
        if(cnt >= k)
        {
            for(i = len - 1, mark = 0; i >= 0; i--)
            {
                if(n[i] == '0')
                {
                    mark++;
                    continue;
                }
                if(mark >= k)break;
                ans++;
            }
        }
        else
        {
            for(i = 0; i < len; i++)
            {
                if(check_zero(i))break;
                if(n[i] != '0')ans++;
            }
            ans += cnt - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
