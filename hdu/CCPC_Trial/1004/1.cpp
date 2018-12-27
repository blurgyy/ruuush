#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#define maxn 1000010
using namespace std;

int T;
int next[maxn];
char a[maxn], b[maxn];

void get_next(char * a, int next[])
{
    memset(next, 0, sizeof(next));
    int lena = strlen(a);
    int j = -1, i = 0;
    next[0] = -1;
    while(i < lena-1)
    {
        if(j == -1 || a[i] == a[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else j = next[j];
    }
}

void out(int len)
{
    for(int i = 0; i < len; i++)
        printf("%d ", next[i]);
    printf("\n");
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s%s", a, b);
        int len1 = strlen(a), len2 = strlen(b);
        reverse(a, a + len1);
        reverse(b, b + len2);
        get_next(b, next);
        //out(len2);

    }
}

/**

ababbababbababba
jkljafkdl

*/
