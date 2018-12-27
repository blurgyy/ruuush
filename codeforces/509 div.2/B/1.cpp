#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll a, b, x, y;

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    while(~scanf("%I64d%I64d%I64d%I64d", &a, &b, &x, &y)){
        ll g = gcd(x, y);
        x /= g;
        y /= g;
        ll a1 = a / x;
        ll b1 = b / y;
        printf("%I64d\n", min(a1, b1));
    }
    return 0;
}