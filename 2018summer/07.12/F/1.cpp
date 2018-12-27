#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n;
ll pfct[2][110];

int main(){
    while(~scanf("%lld", &n)){
        memset(pfct, 0, sizeof(pfct));
        ll top = cbrt(n) + 2, p = 0;
        top = min(top, n + 1);
        for(int i = 2; i < top; ++ i){
            if(n % i == 0){
                pfct[0][p] = i;
                while(n % i == 0){
                    pfct[1][p] += 1;
                    n /= i;
                }
                p ++;
            }
        }
        printf("n = %lld\n", n);
        for(int i = 0; i < p; ++ i)
            printf("cnt[%lld] = %lld\n", pfct[0][i], pfct[1][i]);
    }
    return 0;
}