#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int main()
{
    int s, d;
    while(~scanf("%d%d", &s, &d))
    {
        int ans;
        if(d > s*4)ans = 10 * s - 2 * d;
        else if(2*d > s*3)ans = 8 * s - 4 * d;
        else if(3*d > s*2)ans = 6 * s - 6 * d;
        else if(4*d > s)ans = 3 * s - 9 * d;
        else ans = -1;
        if(ans < 0)printf("Deficit\n");
        else printf("%d\n", ans);
    }
    return 0;
}
