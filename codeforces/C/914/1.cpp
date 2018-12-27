#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;
const ll mod = 1e9 + 7;

char a[maxn];
ll k, ans[maxn], frac[maxn<<1];

ll Get_inv(ll n){
    if(n == 1)return 1;
    return (mod - mod / n) * Get_inv(mod % n) % mod;
}

void Preprocess(){
    memset(ans, 0, sizeof(ans));
    for(int i = 1; i <= 2010; ++ i)
        frac[i] = frac[i-1] * i % mod;
    for(int i = 1; i <= 1000; ++ i){
        for(int j = 0; j <= 1000; ++ j){
            ans[i] += frac[i+j-1] * Get_inv(frac[i] * frac[j]) % mod;
        }
    }
}

int main(){
    Preprocess();
    while(~scanf("%s%I64d", a, &k)){
        
    }
    return 0;
}

/**

10. 100. 1000. 10000
11. 101. 110. 1001. 1010. 1100...
111. 1110.1101.1011.11100.11010


1100
1010
1001
0110
0101
0011

*/