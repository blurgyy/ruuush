#include <cstdio>
#include <algorithm>
typedef long long ll;
const int maxn = 1000010;

int T;
ll n;

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%lld", &n);
        if(!(n % 3)){
            n /= 3;
            printf("%lld\n", n * n * n);
        }
        else if(!(n % 4)){
            n /= 4;
            printf("%lld\n", 2 * n * n * n);
        }
        else if(!(n % 6)){
            n /= 6;
            printf("%lld\n", 6 * n * n * n);
        }
        else {
            printf("-1\n");
        }
    }
    return 0;
}