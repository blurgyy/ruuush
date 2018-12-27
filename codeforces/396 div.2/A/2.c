#include<string.h>
#include<stdio.h>
#define maxn 100010
int main()
{
    char a[maxn], b[maxn];
    int i, f = 0;
    while(scanf("%s%s", a, b) != EOF)
    {
        int lena = strlen(a);
        int lenb = strlen(b);
        if(lena == lenb)
        {
            for(i = 0; i < lena; i++)
            {
                if(a[i] == b[i])continue;
                break;
            }
            if(i != lena)printf("%d\n", lena);
            else printf("-1\n");
        }
        else printf("%d\n", lena > lenb ? lena : lenb);
    }
    return 0;
}
