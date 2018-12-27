#include<cstdio>
#include<map>
#include<algorithm>
#include<string.h>
#define maxn 100010
#define ll long long
using namespace std;

int main()
{
    int n;
    ll k, temp;
    map<ll, int> mp;
    map<int, int> m;
    int orig[maxn] = {0}, dif[maxn] = {0};
    while(~scanf("%d%d", &n, &k))
    {
        temp = k;
        int i;
        for(i = 0; i < n; i++)
        {
            scanf("%d", orig + i);
            m[orig[i]]++;
            if(i)dif[i] = dif[i-1] + dif[i];
            else dif[i] = orig[i];
        }
        mp[1] = 1;
        if(k != 1)
            while(1)
            {
                for(i = 0; i < n; i++)
                    if(m.find(orig[i] + 1) != m.end())
                temp *= k;
                if(temp >= 1e15)break;
                mp[temp] = 1;
            }
    }
}
