#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;

int pos1, pos2, m, n, lake;
set<int> res;

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a%b);
}

void bs(int left, int right)
{
    //printf("l: %d\tr: %d\n", left, right);
    if(left >= right)return;
    int mid = (left + right)>>1;
    int result = (m - n) * mid + pos1 - pos2;
    if(result % lake == 0)res.insert(mid);
    if(result / lake > (m-n))bs(left, mid);
    else bs(mid+1, right);
}

int main()
{
    while(~scanf("%d%d%d%d%d", &pos1, &pos2, &m, &n, &lake))
    {
        res.clear();
        int g = gcd(m, n);
        int dist = pos1 - pos2;
        if(dist % g)
        {
            printf("Pat\n");
            continue;
        }
        bs(0, 100000000);
        set<int>::iterator i = res.begin();
        for(i; i != res.end(); i++)
            printf("%d ", *i);
        printf("\n\n");
        int ans = *res.begin();
        printf("asn = %d\n", ans);
    }
    return 0;
}
