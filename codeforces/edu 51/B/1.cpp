#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 300010;

ll l, r;

int main(){
    while(~scanf("%I64d%I64d", &l, &r)){
        printf("YES\n");
        for(ll i = l+1; i <= r; i += 2){
            printf("%I64d %I64d\n", i-1, i);
        }
    }
    return 0;
}