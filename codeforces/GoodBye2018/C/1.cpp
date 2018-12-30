#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e9;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n;

int main(){
    while(~scanf("%d", &n)){
        int top = sqrt(n) + 1;
        set<ll> ans;
        for(int i = 1; i <= top; ++ i){
            if(n % i == 0){
                ll cnt = n / i;
                ll topval = 1ll + 1ll * (cnt - 1) * i;
                ans.insert((1ll + topval) * cnt / 2);

                int tmp = cnt;
                cnt = i;
                topval = 1ll + 1ll * (cnt - 1) * tmp;
                ans.insert((1ll + topval) * cnt / 2);
            }
        }
        for(set<ll>::iterator i = ans.begin(); i != ans.end(); ++ i){
            printf("%I64d ", *i);
        }
        printf("\n");
    }
    return 0;
}
