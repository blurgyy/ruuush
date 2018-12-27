#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 3000
using namespace std;

int T;
char a[maxn] = {0}, b[maxn] = {0};

int count()
{
    int len = strlen(b);
    int ans = 0;
    for(int i = 0; i < len; i++)
        if(b[i] == '*')ans++;
    return ans;
}

int main()
{
    /*
    for(int i = 0; i < maxn; i++)
        if(i&1)a[i] = 'a';
        else a[i] = '*';
    */
    printf("%s\n", a);
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s%s", a, b);
        int len1 = strlen(a), len2 = strlen(b);
        int cnt = count();
        while(cnt--)
        {
            for(int i = 0; i < len2; i++)
            {
                if(b[i] == '*' && i != len2-1)
                {
                    if(b[i-1] == b[i+1] && b[i-1] != '.')
                    {
                        for(int j = (b[i+2] == '*' ? i+2 : i+1); j < len2; j++)
                            b[j] = b[j+1];
                        len2 = strlen(b);
                    }
                    int c = 0;
                    char ch = b[i-1]
                    for(int j = i-1; j >= 0; j--)
                        if(b[i] == ch)c++;
                        else break;
                    if(c > 1)
                }
            }
            printf("%s\n", b);
        }
        printf("%s\n", b);
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
    }
    return 0;
}
/**

abdcer
.bd.*.*.*.*.*

aaaaaaaaaa
.*a

b
b.*

a
c*a*.*

abc
abd*

*/
