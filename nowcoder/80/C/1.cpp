#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const ll mod = 998244353;

ll p, fac[maxn];

int main(){
    fac[1] = 1;
    while(~scanf("%lld", &p)){
        for(int i = 2; i <= p; ++ i)
            fac[i] = fac[i-1] * i % mod;
        printf("%lld\n", fac[p] * fac[p] % mod * 2 % mod);
    }
    return 0;
}