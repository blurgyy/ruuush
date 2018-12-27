///高精度除法
#include<cstdio>
#include<math.h>
#include<cstring>
#include<algorithm>
#define maxn 110
#define ll long long
using namespace std;

char in[30];
ll n, m, Ans;
char num[maxn];
char ans[maxn];
int p;

int GetLen(ll n)
{
    int len = 0;
    while(n > 0)
    {
        num[p++] = n%10 + '0';
        n /= 10;
        len++;
    }
    return len;
}

int GetLen2(ll n)
{
    int len = 0;
    while(n > 0)
    {
        n /= 10;
        len++;
    }
    return len;
}

void GetNum(int len)
{
    int len2 = GetLen(n);
    reverse(num, num + len2);
    for(int i = len2; i < len2 + 3*len; i++)
        num[i] = '0';
}

void out(char * ans)
{
    int start = 0;
    while(ans[start] < '0' || ans[start] > '9')start++;
    int cnt = 2, len = strlen(in);
    while(in[cnt] == '0')cnt++;
    cnt -= 2;
    while(ans[start] == '0')start++;
    start -= cnt;
    for(int i = start; i < p; i++)
        printf("%c", ans[i]);
}

void init()
{
    n = 0;
    m = 1;
    p = 0;
    Ans = 0;
    memset(num, 0, sizeof(num));
    memset(ans, 0, sizeof(ans));
}

int main()
{
    while(~scanf("%s", in))
    {
        init();
        int len = strlen(in);
        for(int i = len-1; i >= 2; i--)
        {
            n += (in[i]-'0') * m;
            m *= 8;
        }
        //printf("%lld\n", n);
        len -= 2;
        GetNum(len);
        //printf("%s\n", num);
        n = 1;
        while(len--)
            n *= 8;
        ll nowDeno = 0;
        int top = 0;
        int n_len = GetLen2(n);
        int num_len = strlen(num);
        while(top < num_len)
        {
            while(GetLen2(nowDeno) < n_len || nowDeno < n)
            {
                nowDeno *= 10;
                nowDeno += num[top++] - '0';
                //printf("nowDeno = %lld, n = %lld\n", nowDeno, n);
                if(top >= num_len)break;
                if(nowDeno < n)ans[p++] = '0';
            }
            ans[p++] = nowDeno / n + '0';
            nowDeno %= n;
        }
        printf("%s [8] = 0.", in);
        out(ans);
        printf(" [10]\n");
    }
    return 0;
}

/**

0.75 [8] = 0.953125 [10]
0.0001 [8] = 0.000244140625 [10]
0.01234567 [8] = 0.020408093929290771484375 [10]

*/
