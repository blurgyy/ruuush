#include<cstdio>
#include<string.h>
#include<algorithm>
#define maxn 1010
using namespace std;

void change(char s[], int pos, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        s[i] += pos;
        if(s[i] > 'Z')s[i] -= 26;
    }
}

int main()
{
    char mes[maxn] = {0};
    char orig[maxn] = {0};
    char s[maxn] = {0};
    scanf("%s%s", mes, orig);
    int len = strlen(mes);
    sort(orig, orig + len);
    int i;
    for(i = 1; i < 26; i++)
    {
        strcpy(s, mes);
        change(s, i, len);
        sort(s, s + len);
        if(!strcmp(s, orig))break;
    }
    if(i != 26)printf("YES\n");
    else printf("NO\n");
    return 0;
}
