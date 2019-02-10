#include <bits/stdc++.h>
using namespace std;
const int maxk = 1010;

int n, k;

int main(){
    while(~scanf("%d%d", &n, &k)){
        int ans = -1;
        for(int mod = 1; mod < k; ++ mod){
            if(n % mod == 0){
                ans = n * k / mod + mod;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}