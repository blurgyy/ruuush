#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main()
{
    bool flag = true;
    int l[5], s[5], r[5], p[5];
    for(int i = 1; i <= 4; i++)
    {
        scanf("%d%d%d%d", l+i, s+i, r+i, p+i);
    }
    if(p[1] && (l[1] || s[1] || r[1] || s[3] || l[2] || r[4]))flag =false;
    if(p[2] && (l[2] || s[2] || r[2] || s[4] || r[1] || l[3]))flag = false;
    if(p[3] && (l[3] || s[3] || r[3] || s[1] || l[4] || r[2]))flag = false;
    if(p[4] && (l[4] || s[4] || r[4] || l[1] || r[3] || s[2]))flag = false;
    if(!flag)printf("YES\n");
    else printf("NO\n");
    return 0;
}
