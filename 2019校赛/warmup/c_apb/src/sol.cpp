#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int T;
ll a, b;

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%lld%lld", &a, &b);
        printf("%lld\n", a+b);
    }
    return 0;
}
