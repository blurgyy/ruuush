#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n, m, a;
    while(~scanf("%I64d%I64d%I64d", &n, &m, &a)){
        n += (a - (n%a)) * (n%a>0);
        m += (a - (m%a)) * (m%a>0);
        printf("%I64d\n", (m/a) * (n/a));
    }
    return 0;
}