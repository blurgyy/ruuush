#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1010
using namespace std;

char ans[maxn], in[maxn];

void rev(char * a)
{
    int len = strlen(a);
    for(int i = 0; i < len/2; i++)
        swap(a[i], a[len-i-1]);
}

void add()
{
    char tmp[maxn];
    strcpy(tmp, ans);
    memset(ans, 0, sizeof(ans));
    int p1 = strlen(in) - 1, p2 = strlen(tmp) - 1;
    int p = 0;
    while(p1 >= 0 && p2 >= 0)
        ans[p++] = in[p1--] + tmp[p2--] - '0';
    while(p1 >= 0)
        ans[p++] = in[p1--];
    while(p2 >= 0)
        ans[p++] = tmp[p2--];
    for(int i = 0; i < p; i++)
        if(ans[i] > '9')
        {
            ans[i] -= 10;
            ans[i+1]++;
        }
    if(ans[p] > 0)ans[p] += '0';
    rev(ans);
}

int main()
{
    while(strcmp(in, "0"))
    {
        scanf("%s", in);
        add();
    }
    printf("%s\n", ans);
}
