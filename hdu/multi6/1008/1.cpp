#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 6000
using namespace std;

char s[maxn];
int len;
int m;
bool check(int k)
{
    for(int i = 0; )
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &m);
        scanf("%s", s);
        len = strlen(s);
        int a = 0, b = len/2 + 1;
        while(b - a != 1)
        {
            int mid = (a + b)>>1;
            if(check(mid))a = mid;
            else b = mid;
        }
    }
}
