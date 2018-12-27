#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 1010

int t, n;
int st[maxn];
int in[maxn];

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        int p = 0;
        for(int i = 0; i < n; i++)
            scanf("%d", in + i);
        sort(in, in + n);
        if(n % 2 == 1)
        {
            st[p++] = in[0] - 1;
            for(int i = 2; i < n; i += 2)
                st[p++] = in[i] - in[i-1] - 1;
        }
        else
        {
            for(int i = 1; i < n; i += 2)
                st[p++] = in[i] - in[i-1] - 1;
        }
        int ans = st[0];
        for(int i = 1; i < p; i++)
            ans = st[i] ^ ans;
        if(ans)printf("Georgia will win\n");
        else printf("Bob will win\n");
    }
    return 0;
}
