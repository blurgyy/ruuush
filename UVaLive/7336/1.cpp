///Oh what a 水题
///少做水题。。

///@brief 以及今天发现这些什么Doxygen语法用来注释。。？
///改天Google学学

#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 50010
using namespace std;

int T, Q;
int d[maxn], s[maxn];
char r[maxn][2];
int sus[maxn], normal[maxn];
int ps, pn;
int ans;

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        memset(sus, 0, sizeof(sus));
        memset(normal, 0, sizeof(normal));
        ps = 0;
        pn = 0;
        ans = 0;
        scanf("%d", &Q);
        for(int i = 0; i < Q; ++i)
        {
            scanf("%d%d%s", d+i, s+i, r+i);
            if(s[i] == 1 && !strcmp(r[i], "c"))
                sus[ps++] = d[i];
            if(s[i] == 0 && !strcmp(r[i], "i"))
                normal[pn++] = d[i];
        }
        sort(sus, sus + ps);
        sort(normal, normal + pn);
        for(int i = ps-1; i >= 0; --i)
        {
            for(int j = 0; j < pn; ++j)
            {
                if(normal[j] >= sus[i])break;
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
