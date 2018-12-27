#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 300010;
const ll mod = 1000000007;

int n;
ll a[maxn], pre[maxn], su[maxn];
ll ans;
ll rec[maxn];

ll fp(ll a, int b)
{
    ll Ans = 1;
    while(b)
    {
        if(b&1)Ans = (Ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return Ans;
}

void Get_fix(){
    memset(pre, 0, sizeof(pre));
    memset(su, 0, sizeof(su));
    pre[0] = a[0];
    su[n-1] = a[n-1];
    for(int i = 1; i < n; ++ i)
        pre[i] = (pre[i-1] + a[i]) % mod;
    for(int i = n-1; i >= 0; -- i)
        su[i] = (a[i] + su[i+1]) % mod;
}

void out(){
    for(int i = 0; i < n; ++ i)
        printf("%I64d ", pre[i]);
    printf("\n");
    for(int i = 0; i < n; ++ i)
        printf("%I64d ", su[i]);
    printf("\n");
}

int main(){
    for(int i = 0; i < maxn; ++ i){
        rec[i] = fp(2LL, i);
    }
    while(~scanf("%d", &n)){
        ans = 0;
        for(int i = 0; i < n; ++i)
            scanf("%I64d", a + i);
        sort(a, a + n);

        Get_fix();

        for(int len = 0; len < n; ++ len){
            //printf("%d, %d\n", su[n-len], pre[len-1]);
            ans += (rec[len] * ((su[n-len-1] - pre[len]) % mod)) % mod;
            ans %= mod;
        }
        printf("%I64d\n", (ans + mod) % mod);
    }
    return 0;
}