#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 300010;

int n;
ll a[maxn];

ll sq(ll x){
    return x * x;
}

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i) scanf("%lld", a + i);
        sort(a, a + n);
        ll ans = 0;
        int mid = n >> 1;
        for(int i = 0; i < mid; ++ i){
            ans += sq(a[i] + a[n-1-i]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}