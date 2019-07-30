#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int mod = 998244353;

int w, h;
ll pow2[maxn];

void init(){
    pow2[0] = 1;
    for(int i = 1; i < maxn; ++ i){
        pow2[i] = pow2[i-1] * 2 % mod;
    }
}

int main(){
    init();
    while(~scanf("%d%d", &w, &h)){
        printf("%lld\n", pow2[w + h]);
    }
    return 0;
}
