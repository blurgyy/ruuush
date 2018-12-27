#include<cstdio>
#include<string.h>
#include<algorithm>
#define maxn 1010
using namespace std;

bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    char a[maxn] = {0}, b[maxn] = {0}, s[maxn] = {0};
    int cnta[30] = {0}, cntb[30] = {0};
    while(~scanf("%s%s", a, b))
    {
        memset(cnta, 0, sizeof(cnta));
        memset(cntb, 0, sizeof(cntb));
        int i;
        int len = strlen(a);
        for(i = 0; i < len; i++)
        {
            cnta[a[i]-'A']++;
            cntb[b[i]-'A']++;
        }
        sort(cnta, cnta + 26, cmp);
        sort(cntb, cntb + 26, cmp);
        for(i = 0; i < 26; i++)
        {
            if(cnta[i] != cntb[i])break;
        }
        if(i == 26)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
