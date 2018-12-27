#include<cstdio>
#include<map>
#include<cstring>
#include<algorithm>
#define ll long long
#define maxn 10000010
using namespace std;

map<int, int> faca, facb;
int n;
ll a, b;
ll cubic[maxn];

void init()
{
    faca.clear();
    facb.clear();
}

ll sch(int left, int right, ll e)
{
    //printf("left = %d, right = %d\n", left, right);
    if(left >= right)return right;
    int mid = (left + right)>>1;
    if(cubic[mid] >= e)return sch(left, mid, e);
    return sch(mid+1, right, e);
}

int main()
{
    for(ll i = 1; i <= 1000000; i++)
        cubic[i] = i * i * i;
    while(~scanf("%d", &n))
    {
        while(n--)
        {
            scanf("%I64d%I64d", &a, &b);
            init();
            ll prod = a * b;
            ll pos = sch(1, 1000000, prod);
            if(pos*pos*pos == prod && a%pos == 0 && b%pos == 0)printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
