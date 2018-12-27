#include<cstdio>
typedef long long ll;

ll T, n, num, ans;

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a%b);
}

int main(){
    scanf("%lld", &T);
    while(T--){
        ans = 1;
        scanf("%lld", &n);
        while(n--){
            scanf("%lld", &num);
            ans = ans * num / gcd(ans, num);
        }
        printf("%lld\n", ans);
    }
    return 0;
}