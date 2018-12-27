#include<stdio.h>
#include<string.h>
#include<algorithm>
#define maxn 200010
using namespace std;

char t[maxn], p[maxn], targ[maxn] = {0};
int per[maxn];

int check(int len)
{
    int i, tag = 0;
    for(i = 0; i < len; i++)
    {
        if(targ[tag] == p[tag])
        {
            tag++;
            check(len);
        }
    }
    if(tag == strlen(p))return 1;
    return 0;
}

int main()
{
    while(~scanf("%s%s", t, p))
    {
        int i, len = strlen(t), ans = 0;
        for(i = 1; i <= len; i++)
        {
            scanf("%d", per + i);
        }
        for(i = len; i >= 1; i--)
        {
            targ[per[i]-1] = t[per[i]-1];
            if(check(len))break;
            ans++;
        }
        printf("%d\n", len - ans);
    }
    return 0;
}
