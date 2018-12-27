#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, k;

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    while(~scanf("%I64d%I64d%I64d", &n, &m, &k)){
        int nn = n, mm = m, kk = k;
        ll gnk = gcd(n, k);
        n /= gnk;
        k /= gnk;
        ll gmk = gcd(m, k);
        m /= gmk;
        k /= gmk;
        if(k <= 2){
            printf("YES\n");
            printf("0 0\n");
            if(k == 1){
                if(n * 2 <= nn){
                    n *= 2;
                }
                else{
                    m *= 2;
                }
            }
            printf("0 %I64d\n%I64d 0\n", m, n);
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}