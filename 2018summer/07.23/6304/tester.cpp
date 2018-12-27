#include <cstdio>
#include <cstring>
typedef long long ll;
const int maxn = 1000010;
const int mod = 1e9 + 7;

ll a[maxn], sum[maxn];

int main(){
    //freopen("fakestd.out", "w", stdout);
    memset(a, 0, sizeof(a));
    memset(sum, 0, sizeof(sum));
    a[1] = a[2] = 1;
    sum[1] = 1;
    sum[2] = 2;
    for(int i = 3; i < maxn; ++ i){
        a[i] = (a[i-a[i-1]] + a[i-1-a[i-2]]) % mod;
        sum[i] = (sum[i-1] + a[i]) % mod;
    }
    int top = 35;
    for(int i = 1; i <= top; ++ i){
        printf("%lld%c ", a[i], ",\n"[i == top]);
    }
    return 0;
    for(int i = 1; i < maxn; ++ i){
        //printf("%lld\n", sum[i]);
        printf("a[%d] = %lld, sum[%d] = %lld\n", i, a[i], i, sum[i]);
    }
    return 0;
}