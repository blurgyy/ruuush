#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 50010;
const int mod = 998244353;

int T, n, in;
int zero[30], one[30];
ll rec[30] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912};
ll ans;

void Insert(int num){
    bool not_added = true;
    for(int i = 0; i < 30; ++ i){
        if(num&1){
            ++ one[i];
            if(not_added){
                ans += rec[i] * zero[i] % mod;
                not_added = false;
            }
        }
        else{
            ++ zero[i];
            if(not_added){
                ans += rec[i] * one[i] % mod;
                not_added = false;
            }
        }
    }
}

int main(){
    scanf("%d", &T);
    while(T--){
        memset(zero, 0, sizeof(zero));
        memset(one, 0, sizeof(one));
        ans = 0;

        scanf("%d", &n);
        while(n--){
            scanf("%d", &in);
            Insert(in);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

/**

2
5
4 0 2 7 0
5
2 6 5 4 0

*/