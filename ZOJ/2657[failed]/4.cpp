///Screw it
///I'm going to solve some LCA problems
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int pos1, pos2, m, n, l;

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a%b);
}

int main()
{
    while(~scanf("%d%d%d%d%d", &pos1, &pos2, &m, &n, &l))
    {
        int g = gcd(m, n);
        int dist = pos1 - pos2;
        if(dist % g)
        {
            printf("Pat\n");
            continue;
        }
        int ans;
        ans = abs((l + dist) / (m - n));
        printf("%d\n", ans);
    }
    return 0;
}
