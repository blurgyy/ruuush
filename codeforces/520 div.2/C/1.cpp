#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 100010;
const int mod = 1e9 + 7;

int n, q, l, r;
int val[maxn];
char x[maxn];
ll pow2[maxn];

ll calc(int cnt, int len){
    ll ret = (pow2[cnt] - 1 + mod) % mod;
    ret = (ret + ret * ((pow2[len-cnt] - 1 + mod) % mod) % mod) % mod;
    return ret;
}

int main(){
    pow2[0] = 1;
    for(int i = 1; i < maxn; ++ i) pow2[i] = pow2[i-1] * 2 % mod;

    while(~scanf("%d%d%s", &n, &q, x+1)){
        val[0] = 0;
        for(int i = 1; i <= n; ++ i){
            val[i] = val[i-1] + x[i] - '0';
        }
        while(q --){
            scanf("%d%d", &l, &r);
            int cnt = val[r] - val[l-1];
            int len = r - l + 1;
            printf("%I64d\n", calc(cnt, len));
        }
    }
    return 0;
}

/*

32 5
11111111111111111111111111111111

*/