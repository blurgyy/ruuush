#include<bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    ll m, k;
    while(scanf("%lld%lld", &m, &k) != EOF)
        printf("%lld\n", (m - k + 1) * k);
    return 0;
}
