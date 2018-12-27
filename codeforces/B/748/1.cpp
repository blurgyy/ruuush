#include<stdio.h>
#include<string.h>
#define maxn 1010

char ans[maxn][3];

void change(char s[], int n, char c1, char c2)//s[]为要替换的字符数组；n为字符c1所在位置； c1为要被替换为c2的字符
{
    int i;
    for(i = n; i < strlen(s); i++)
    {
        if(s[i] == c1)s[i] = c2;
        else if(s[i] == c2)s[i] = c1;
    }
}

int main()
{
    char s1[maxn], s2[maxn];
    while(~scanf("%s\n%s", s1, s2))
    {
        int cnt = 0;
        int len = strlen(s1);
        int i;
        for(i = 0; i < len; i++)
        {
            if(s1[i] == s2[i])continue;
            ans[cnt][1] = s1[i];
            ans[cnt++][2] = s2[i];
            change(s2, i, s2[i], s1[i]);
        }
        if(strcmp(s1, s2))printf("-1\n");
        else
        {
            printf("%d\n", cnt);
            for(i = 0; i < cnt; i++)
                printf("%c %c\n", ans[i][1], ans[i][2]);
        }
    }
    return 0;
}
