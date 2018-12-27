#include<stdio.h>
#include<string.h>
#define maxn 510
int main()
{
    char s[maxn];
    while(~scanf("%s", s))
    {
        int i, j, count = 0, len = strlen(s);
        for(i = 0; i < len; i++)
        {
            if(s[i] == 'a' + count || s[i] == '0')
            {
                int f = 0;
                if(s[i] == 'a' + count)
                {
                    for(j = i; j < len; j++)
                    {
                        if(s[j] == 'a' + count)
                        {
                            f = 1;
                            s[j] = '0';
                        }
                    }
                }
                if(f)count++;
            }
            else break;
        }
        for(i = 0; i < len; i++)
        {
            if(s[i] != '0')break;
        }
        if(i == len)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
