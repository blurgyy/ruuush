#include<stdio.h>
#include<string.h>
#define maxn 1010
char s[maxn], t[maxn], ans[maxn][3];
int tag = 0;

void change(int i)
{
    char temp1 = s[i], temp2 = t[i];
    for(i = 0; i < strlen(s); i++)
    {
        if(t[i] == temp2)
        {
            t[i] = temp1;
            continue;
        }
        if(t[i] == temp1)
        {
            t[i] = temp2;
            continue;
        }
    }
}

int check()
{
    int i;
    char use[27] = {0};
    for(i = 0; i < tag; i++)
    {
        use[ans[i][1]-'a'+1]++;
        use[ans[i][2]-'a'+1]++;
        int j;
        for(j = 1; j < 27; j++)
            if(use[j] > 1)return 0;
    }
    return 1;
}

void output()
{
    int i;
    for(i = 0; i < strlen(s); i++)
        printf("%c", s[i]);
    printf("\n");
    for(i = 0; i < strlen(t); i++)
        printf("%c", t[i]);
    printf("\n\n");
}

int main()
{
    while(~scanf("%s\n%s", s, t))
    {
        int i, len = strlen(s), cnt = 0, f = 1;
        for(i = 0; i < len; i++)
        {
            /*printf("1:");
            output();*/
            if(s[i] == t[i])continue;
            ans[tag][1] = s[i];
            ans[tag++][2] = t[i];
            change(i);
            cnt++;
            if(check() == 0)
            {
                f = 0;
                break;
            }
            /*printf("2:");
            output();*/
            if(strcmp(s, t))continue;
            break;
        }
        if(!f || strcmp(s, t))printf("-1\n");
        else
        {
            printf("%d\n", cnt);
            for(i = 0; i < tag; i++)
            {
                printf("%c %c\n", ans[i][1], ans[i][2]);
            }
        }
    }
    return 0;
}
